//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "Vault.h"

#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Widgets/VaultWidget.h"

//----------------------------------------------------------------------------------------------------------------------
AVault::AVault()
{
	PrimaryActorTick.bCanEverTick = true;

	VaultMesh = CreateDefaultSubobject<UStaticMeshComponent>("Vault Mesh");
	
	VaultDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Vault Door Mesh");
	VaultDoorMesh->SetupAttachment(VaultMesh);

	DoorOpenRotator = VaultDoorMesh->GetRelativeRotation() + FRotator(0,90,0);
	
	FrontArrow = CreateDefaultSubobject<UArrowComponent>("Front Arrow");
	FrontArrow->SetupAttachment(VaultMesh);
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::Interaction()
{
	if(bIsFocus || !bCanInteract) return;

	Player->OnFocusMode(FrontArrow->GetComponentTransform(), GetActorRotation());
	
	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetFocusInput();
	controller->SetNewCursorVisibilityState(true);
	controller->OnLeaveFocus.AddDynamic	(this, &AVault::LeaveFocus);
	
	bIsFocus = true;

	VaultWidget->AddToViewport(2);
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::BeginPlay()
{
	Super::BeginPlay();

	BindTimeLine();
	
	Player = CastChecked<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
	VaultWidget = CreateWidget<UVaultWidget>(GetWorld(), VaultWidgetBase);
	VaultWidget->OnCodeCorrect.AddDynamic(this, &AVault::OnVaultOpened);
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	OpenVaultDoorTimeLine.TickTimeline(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::LeaveFocus()
{
	bIsFocus = false;
	Player->BackToNormalView(FrontArrow->GetComponentTransform(), ExitingVector, ExitingRotation);
	
	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetNormalInput();
	controller->SetNewCursorVisibilityState(false);
	
	controller->OnLeaveFocus.RemoveDynamic(this, &AVault::LeaveFocus);
	VaultWidget->RemoveFromParent();
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::OnVaultOpened()
{
	bCanInteract = false;
	
	OpenVaultDoorTimeLine.PlayFromStart();
}

#pragma region Time line methods
//----------------------------------------------------------------------------------------------------------------------
void AVault::BindTimeLine()
{
	FOnTimelineFloat OpeningDoorTick;
	OpeningDoorTick.BindUFunction(this, FName("OpeningVaultDoorTick"));
	OpenVaultDoorTimeLine.AddInterpFloat(CurveFloat, OpeningDoorTick);
	
	FOnTimelineEventStatic OpeningDoorFinished;
	OpeningDoorFinished.BindUFunction(this, FName("OpeningVaultDoorFinished"));
	OpenVaultDoorTimeLine.SetTimelineFinishedFunc(OpeningDoorFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::OpeningVaultDoorTick(float deltaSeconds)
{
	auto NewRotation = FMath::Lerp(VaultDoorMesh->GetRelativeRotation(), DoorOpenRotator, deltaSeconds);
	VaultDoorMesh->SetRelativeRotation(NewRotation);
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::OpeningVaultDoorFinished()
{
	VaultMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	VaultDoorMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	LeaveFocus();
}
#pragma endregion 