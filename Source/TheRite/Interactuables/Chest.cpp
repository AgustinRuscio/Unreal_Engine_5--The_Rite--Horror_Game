//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "Chest.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Characters/Alex.h"

static FString MyKeyName;
static PickableItemsID MyKeyId;

//----------------------------------------------------------------------------------------------------------------------
AChest::AChest()
{
	PrimaryActorTick.bCanEverTick = true;

	ChestMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Chest Mesh Component");

	LockMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Lock Mesh Component");
	LockMeshComponent->SetupAttachment(ChestMeshComponent);

	KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Key Mesh Component");
	KeyMeshComponent->SetupAttachment(ChestMeshComponent);
	KeyMeshComponent->SetVisibility(false);
	
	ArrowFocusLocation = CreateDefaultSubobject<UArrowComponent>("Arrow Focus Location Component");
	ArrowFocusLocation->SetupAttachment(ChestMeshComponent);
	
	ArrowEndLocation = CreateDefaultSubobject<UArrowComponent>("Arrow End Key Location Component");
	ArrowEndLocation->SetupAttachment(ChestMeshComponent);

	ChestCollider = CreateDefaultSubobject<UBoxComponent>("Chest Box Component");
	ChestCollider->SetupAttachment(ChestMeshComponent);
}

//----------------------------------------------------------------------------------------------------------------------
void AChest::Interaction()
{
	if(bIsFocus || !bCanInteract) return;
	if(!bIsUnlocked) return;
	
	Player->RemoveFromInventory(MyKeyName, MyKeyId);
	
	Super::Interaction();

	Player->OnFocusMode(ArrowFocusLocation->GetComponentTransform(), GetActorRotation(), false);

	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetFocusInput();
	controller->SetNewCursorVisibilityState(true);
	controller->OnLeaveFocus.AddDynamic	(this, &AChest::LeaveFocus);

	bIsFocus = true;

	InitialKeyLocation = Player->GetActorLocation();

	KeyMeshComponent->SetVisibility(true);
	
	MoveKeyTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void AChest::LeaveFocus()
{
	bIsFocus = false;
	Player->BackToNormalView(ArrowFocusLocation->GetComponentTransform(), ExitingVector, ExitingRotation);

	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetNormalInput();
	controller->SetNewCursorVisibilityState(false);

	controller->OnLeaveFocus.RemoveDynamic(this, &AChest::LeaveFocus);
}

//----------------------------------------------------------------------------------------------------------------------
void AChest::UnlockChest(FString itemName, PickableItemsID id)
{
	bIsUnlocked = true;
	MyKeyName	= itemName;
	MyKeyId		= id;
}

//----------------------------------------------------------------------------------------------------------------------
void AChest::BeginPlay()
{
	Super::BeginPlay();

	Player = CastChecked<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	BindTimeLines();
}

//----------------------------------------------------------------------------------------------------------------------
void AChest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	MoveKeyTimeLine.TickTimeline(DeltaSeconds);
	RotateKeyTimeLine.TickTimeline(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
void AChest::OnLockOpenFinished()
{
	LockMeshComponent->SetSimulatePhysics(false);
	ChestMeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	bCanInteract = false;
	LeaveFocus();
}

//----------------------------------------------------------------------------------------------------------------------
void AChest::BindTimeLines()
{
	FOnTimelineFloat MoveKeyTick;
	MoveKeyTick.BindUFunction(this, FName("MoveKeyTick"));
	MoveKeyTimeLine.AddInterpFloat(FloatCurve, MoveKeyTick);
	
	FOnTimelineEventStatic MoveKeyFinished;
	MoveKeyFinished.BindUFunction(this, FName("MoveKeyFinished"));
	MoveKeyTimeLine.SetTimelineFinishedFunc(MoveKeyFinished);

	FOnTimelineFloat RotateKeyTick;
	RotateKeyTick.BindUFunction(this, FName("RotateKeyTick"));
	RotateKeyTimeLine.AddInterpFloat(FloatCurve, RotateKeyTick);
	
	FOnTimelineEventStatic RotateKeyFinished;
	RotateKeyFinished.BindUFunction(this, FName("RotateKeyFinished"));
	RotateKeyTimeLine.SetTimelineFinishedFunc(RotateKeyFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void AChest::MoveKeyTick(float DeltaSeconds)
{
	auto newLocation = FMath::Lerp(InitialKeyLocation, ArrowEndLocation->GetComponentLocation(), DeltaSeconds);

	KeyMeshComponent->SetWorldLocation(newLocation);
}

//----------------------------------------------------------------------------------------------------------------------
void AChest::MoveKeyFinished()
{
	RotateKeyTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void AChest::RotateKeyTick(float DeltaSeconds)
{
	auto mewRotation = FMath::Lerp(KeyMeshComponent->GetComponentRotation().Pitch, EndKeyRotation.Pitch, DeltaSeconds);

	KeyMeshComponent->SetWorldRotation(FRotator(mewRotation, KeyMeshComponent->GetComponentRotation().Yaw, KeyMeshComponent->GetComponentRotation().Roll));
}

//----------------------------------------------------------------------------------------------------------------------
void AChest::RotateKeyFinished()
{
	KeyMeshComponent->DestroyComponent();
	
	LockMeshComponent->PlayAnimation(OpenLockSequence, false);

	if(!GetWorld()->GetTimerManager().IsTimerActive(OpeningLockTimerHandle))
	{
		OpeningLockTimerDelegate.BindLambda([&]
		{
			LockMeshComponent->SetSimulatePhysics(true);
			ChestMeshComponent->PlayAnimation(OpenChestSequence, false);
			
			GetWorld()->GetTimerManager().SetTimer(OpeningChestTimerHandle, this, &AChest::OnLockOpenFinished,OpenChestSequence->GetPlayLength(),false);
		});
		
		GetWorld()->GetTimerManager().SetTimer(OpeningLockTimerHandle, OpeningLockTimerDelegate,OpenLockSequence->GetPlayLength(),false);
	}
	
}