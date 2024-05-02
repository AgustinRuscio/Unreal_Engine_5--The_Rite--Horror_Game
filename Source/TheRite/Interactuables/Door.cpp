//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Door.h"

#include "VectorTypes.h"
#include "Camera/CameraComponent.h"
#include "TheRite/Widgets/LockedWidget.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "TheRite/AlexPlayerController.h"
#include "Blueprint/UserWidget.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	//------- Mesh Creation
	DoorItself = CreateDefaultSubobject<UStaticMeshComponent>("Door Itself");
	
	USceneComponent* NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NewRootComponent"));
	SetRootComponent(NewRootComponent);

	DoorItself->SetupAttachment(NewRootComponent);
	
	DoorItself->SetMobility(EComponentMobility::Movable);
	
	BaseFront = CreateDefaultSubobject<UStaticMeshComponent>("Front base");
	BaseBack = CreateDefaultSubobject<UStaticMeshComponent>("Back base");
	BaseBack->SetMobility(EComponentMobility::Movable);
	BaseFront->SetMobility(EComponentMobility::Movable);

	LatchFront = CreateDefaultSubobject<USkeletalMeshComponent>("Front Latch");
	LatchBack = CreateDefaultSubobject<USkeletalMeshComponent>("Back Latch");
	LatchFront->SetMobility(EComponentMobility::Movable);
	LatchBack->SetMobility(EComponentMobility::Movable);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	
	BaseFront->SetupAttachment(DoorItself);
	BaseBack->SetupAttachment(DoorItself);
	LatchFront->SetupAttachment(DoorItself);
	LatchBack ->SetupAttachment(DoorItself);
	BoxCollision->SetupAttachment(DoorItself);

	//------- Locked Widget 
	LockedWidget = CreateDefaultSubobject<ULockedWidget>("Locked Widget");
}

bool ADoor::IsLocked() const
{
	return bIsLocked;
}

//---------------- Getter Methods
bool ADoor::NeedKey() const
{
	return  bNeedKey;
}

bool ADoor::KeyUnlocked() const
{
	return bKeyUnlocked;
}

//---------------- System Class Methods
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	CreateWidgets();
	
	InitializeNeededValues();

	SetTutorialDoor();
	
	BindTimeLines();
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RunTimeLinesTick(DeltaTime);
	
	CheckCanSound(DeltaTime);

	HoldingTimerRunner(DeltaTime);
	
	CheckDragDoor();
	CheckIfLookingDoor();
}

void ADoor::Interaction()
{
	OnInteractionTrigger.Broadcast(this);
	
	TutorialInteraction();
	
	CheckLocked();
	
	CheckPlayerForward();
}

//---------------- Action Door Methods
void ADoor::ObteinKey()
{
	bKeyUnlocked = true;
}

void ADoor::Open()
{
	TimeLineOpenDoor.PlayFromStart();
}

void ADoor::Close()
{
	TimeLineOpenDoor.ReverseFromEnd();
}

void ADoor::HardClosing()
{
	UGameplayStatics::SpawnSoundAtLocation(this, SFXDoorSlam, GetActorLocation());
	TimeLineHardClosing.Play();
}

void ADoor::AutomaticClose()
{
	TimeLineOpenDoor.ReverseFromEnd();
	UGameplayStatics::PlaySoundAtLocation(this, SFXDoorClinck, GetActorLocation());
}

//---------------- Setter Methods
void ADoor::SetDoorKeyValues(FString itemName, PickableItemsID id)
{
	keyName = itemName;
	keyId = id;
}

void ADoor::SetCanDragFalse()
{
	bcanDrag = false;
}

void ADoor::SetLockedState(bool lockednewState)
{
	bIsLocked = lockednewState;
}

//---------------- Initializer Methods
void ADoor::CreateWidgets()
{
	LockedWidget = CreateWidget<ULockedWidget>(GetWorld(), LockedUI);
	LockedWidget->AddToViewport();
	LockedWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ADoor::InitializeNeededValues()
{
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	FirstYawrotation = DoorItself->GetRelativeRotation().Yaw;
	MaxYawrotation = bFrontOpen ? FirstYawrotation + FrontAngle : FirstYawrotation - FrontAngle;
	
	InitialRot = DoorItself->GetRelativeRotation();
	CurrentRot = DoorItself->GetRelativeRotation();
}

//---------------- Tutorial Methods
void ADoor::SetTutorialDoor()
{
	if(!bIsTutorialDoor) return;
	
	TutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), TutorialUI);
	TutorialWidget->AddToViewport();
	TutorialWidget->SetVisibility(ESlateVisibility::Hidden);

	auto alexController = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	
	if(alexController)
		alexController->OnKeyPressed.AddDynamic(TutorialWidget, &UTutorialWidget::SetKeyMode);
}

void ADoor::TutorialInteraction()
{
	if(bIsTutorialDoor && !bDoOnceTut)
	{
		bDoOnceTut = true;
		TutorialWidget->SetVisibility(ESlateVisibility::Visible);
		
		if (!GetWorldTimerManager().IsTimerActive(TutorialTimerHandle))
		{
			FTimerDelegate timerDelegate;
			timerDelegate.BindLambda([&]
			{
				TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
			});
			
			GetWorldTimerManager().SetTimer(TutorialTimerHandle, timerDelegate, 2.f, false);
		}
	}
}

//---------------- Checker Methods
void ADoor::HoldingTimerRunner(float DeltaTime)
{
	bHolding ? DoorTimer += DeltaTime: DoorTimer = 0;
}

void ADoor::CheckCanSound(float DeltaTime)
{
	if(bCanSoundItsLocked) return;
	
	ItsLockedTimer+= DeltaTime;

	if(ItsLockedTimer > ItsLockedCD)
	{
		bCanSoundItsLocked = true;
		ItsLockedTimer = 0.0f;
	}
}

void ADoor::CheckPlayerForward()
{
	FVector DooraLocation = DoorItself->GetComponentLocation();

	FVector PlayerLocation = Player->GetActorLocation();

	FVector PlayerDirection = PlayerLocation - DooraLocation;

	PlayerDirection.Normalize();

	FRotator DoorRotation = GetActorRotation();
	FVector DooraForwardVector = DoorItself->GetComponentLocation().RightVector;
	
	FVector forwatdRoated = DoorRotation.RotateVector(DooraForwardVector);
	
	float DotProduct = FVector::DotProduct(forwatdRoated, PlayerDirection);

	if (DotProduct > 0.0f)
		bIsPlayerForward = true;
	else if (DotProduct < 0.0f)
		bIsPlayerForward = false;
}

void ADoor::CheckLocked()
{
	if(bIsLocked)
		ItsLocked();
	else
	{
		if(bNeedKey)
		{
			if(bKeyUnlocked)
			{
				if(FirstTimeKeySound == 0)
				{
					FirstTimeKeySound++;
					UGameplayStatics::SpawnSound2D(this, SFXDoorUnlocked);
					Player->RemoveFromInventory(keyName ,keyId);
				}
			}
			else
				ItsLocked();
		}
	}
}



void ADoor::CheckDragDoor()
{
	if(!bcanDrag || bIsLocked || (bNeedKey && !bKeyUnlocked))
		return;
	
	LatchHolding(bHolding);

	if(DoorTimer < DoorOpenOffsetCD) return;
	
	float DoorFloat = Player->GetDoorFloat();

	if(bFrontOpen)
	{
		if(bIsPlayerForward)
			DoorItself->AddLocalRotation(FRotator(0, DoorFloat * -1,0));
		else
			DoorItself->AddLocalRotation(FRotator(0, DoorFloat,0));
	}
	else
	{
		if(bIsPlayerForward)
			DoorItself->AddLocalRotation(FRotator(0, DoorFloat ,0));
		else
			DoorItself->AddLocalRotation(FRotator(0, DoorFloat * -1,0));
	}
			
	float DoorCurrentYaw = DoorItself->GetRelativeRotation().Yaw;
		
	if(bFrontOpen)
	{
		if(DoorCurrentYaw > MaxYawrotation)
			DoorItself->SetRelativeRotation(FRotator(0, MaxYawrotation,0));
		else if(DoorCurrentYaw < FirstYawrotation)
			DoorItself->SetRelativeRotation(FRotator(0, FirstYawrotation,0));
	}
	else
	{
		if(DoorCurrentYaw > FirstYawrotation)
			DoorItself->SetRelativeRotation(FRotator(0, FirstYawrotation,0));
		else if(DoorCurrentYaw < MaxYawrotation)
			DoorItself->SetRelativeRotation(FRotator(0, MaxYawrotation,0));
	}
}

void ADoor::CheckIfLookingDoor()
{
	if(bIsLocked) return;
	
	if(bNeedKey)
		if(!bKeyUnlocked) return;
	
	
	FVector Start = Player->GetCamera()->GetComponentLocation();
	
	FVector distace = Player->GetActorForwardVector() * 300;
	FVector End = Start + distace;

	FHitResult HitResult;

	TArray<AActor*> IgnoredActors;

	bool hit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End,
								 TEnumAsByte<ETraceTypeQuery>(ECollisionChannel::ECC_WorldDynamic),
								 false, IgnoredActors,
								EDrawDebugTrace::None,HitResult, false);
	
	if(hit && HitResult.GetActor() == this )
	{		
		bIsLookingDoor = true;
		bWasLookingDoor = true;
		
		bHolding = Player->IsHoldInteractBTN();

		if(bHolding)
		{
			if(UE::Geometry::Distance(Player->GetActorLocation(), GetActorLocation()) > 500) return;
			
			Player->SetDraggingState(true, this);
			bcanDrag = Player->CheckCanDrag();
		}
		else
		{
			Player->SetDraggingState(false, this);
			bcanDrag = false;
		}
	}
	else
	{
		bIsLookingDoor = false;
		
		if(bWasLookingDoor)
		{
			if(bHolding)
			{
				if(UE::Geometry::Distance(Player->GetActorLocation(), GetActorLocation()) > 500) return;
				
				Player->SetDraggingState(true,this);
				bcanDrag = Player->CheckCanDrag();
			}
			else
			{
				Player->SetDraggingState(false, this);
				bcanDrag = Player->CheckCanDrag();
			
				bWasLookingDoor = false;
			}
		}
	}
}

//---------------- FeedBack Methods
void ADoor::ItsLocked()
{
	if(IsValid(SFXVoiceLocked))
		Player->ForceTalk(SFXVoiceLocked);
	
	LockedWidget->SetVisibility(ESlateVisibility::Visible);
	LatchAnim();
	TimeLineItsLocked.PlayFromStart();
}

void ADoor::LatchAnim()
{
	TimeLineLatchAnim.PlayFromStart();
}

void ADoor::LatchHolding(bool isOppening)
{
	if(isOppening)
		TimeLineLatchHold.PlayFromStart();
	else
		TimeLineLatchHold.ReverseFromEnd();
}

//---------------- TimeLines Methods
void ADoor::BindTimeLines()
{
	//------- Open Close TimeLine
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OpenCloseTimeLineUpdate"));
	TimeLineOpenDoor.AddInterpFloat(CurveOpenDoor, TimelineCallback);
	
	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("OpenCloseTimelineFinished"));
	TimeLineOpenDoor.SetTimelineFinishedFunc(TimelineFinishedCallback);

	//------- Its locked timeline
	FOnTimelineFloat LockedTimelineCallback;
	LockedTimelineCallback.BindUFunction(this, FName("ItLockedTimeLineUpdate"));
	TimeLineItsLocked.AddInterpFloat(ItsLockedCurve, LockedTimelineCallback);
	
	FOnTimelineEventStatic LockedTimelineFinishedCallback;
	LockedTimelineFinishedCallback.BindUFunction(this, FName("ItLockedTimelineFinished"));
	TimeLineItsLocked.SetTimelineFinishedFunc(LockedTimelineFinishedCallback);
	
	//------- Latch Anim timeline
	FOnTimelineFloat LatchAnimTimelineCallback;
	LatchAnimTimelineCallback.BindUFunction(this, FName("LatchAnimTimeLineUpdate"));
	TimeLineLatchAnim.AddInterpFloat(ItsLockedCurve, LatchAnimTimelineCallback);
	
	FOnTimelineEventStatic LatchAnimTimelineFinishedCallback;
	LatchAnimTimelineFinishedCallback.BindUFunction(this, FName("LatchAnimTimelineFinished"));
	TimeLineLatchAnim.SetTimelineFinishedFunc(LatchAnimTimelineFinishedCallback);

	//------- Latch Hold timeline
	FOnTimelineFloat LatchHoldTimelineCallback;
	LatchHoldTimelineCallback.BindUFunction(this, FName("LatchHoldTimeLineUpdate"));
	TimeLineLatchHold.AddInterpFloat(LatchHoldCurve, LatchHoldTimelineCallback);
	
	FOnTimelineEventStatic LatchHoldTimelineFinishedCallback;
	LatchHoldTimelineFinishedCallback.BindUFunction(this, FName("LatchHoldTimelineFinished"));
	TimeLineLatchHold.SetTimelineFinishedFunc(LatchHoldTimelineFinishedCallback);
	
	//------- Hard Closing timeline
	FOnTimelineFloat HardClosingTimelineCallback;
	HardClosingTimelineCallback.BindUFunction(this, FName("HardClosingTimeLineUpdate"));
	TimeLineHardClosing.AddInterpFloat(HardClosingCurve, HardClosingTimelineCallback);
	
	FOnTimelineEventStatic HardClosingTimelineFinishedCallback;
	HardClosingTimelineFinishedCallback.BindUFunction(this, FName("HardClosingTimelineFinished"));
	TimeLineHardClosing.SetTimelineFinishedFunc(HardClosingTimelineFinishedCallback);
}

void ADoor::RunTimeLinesTick(float DeltaTime)
{
	TimeLineOpenDoor.TickTimeline(DeltaTime);
	TimeLineItsLocked.TickTimeline(DeltaTime);
	TimeLineLatchAnim.TickTimeline(DeltaTime);
	TimeLineHardClosing.TickTimeline(DeltaTime);
	TimeLineLatchHold.TickTimeline(DeltaTime);
}


void ADoor::OpenCloseTimeLineUpdate(float value)
{
	float newRoll = FMath::Lerp(0,90, value);
	
	DoorItself->SetRelativeRotation(FRotator(0,newRoll, 0));
}

void ADoor::OpenCloseTimelineFinished()
{
	CurrentRot = DoorItself->GetRelativeRotation();
}


void ADoor::ItLockedTimeLineUpdate(float value)
{
	float TargetYaw = InitialRot.Yaw + 5.0f;
	float NewYaw = FMath::Lerp(InitialRot.Yaw, TargetYaw, value);

	DoorItself->SetRelativeRotation(FRotator(0, NewYaw, 0));
}

void ADoor::ItLockedTimelineFinished()
{
	UGameplayStatics::PlaySound2D(this, SFXDoorLocked);
	LockedWidget->SetVisibility(ESlateVisibility::Hidden);
	++AudioCounterItsLocked;
	
	CurrentRot = DoorItself->GetRelativeRotation();
}


void ADoor::LatchAnimTimeLineUpdate(float value)
{
	float lerpValue = FMath::Lerp(5, 50, value);
	LatchFront->SetRelativeRotation(FRotator(lerpValue, 0, 0));
	LatchBack->SetRelativeRotation(FRotator(lerpValue, 0, -180));
}

void ADoor::LatchAnimTimelineFinished() { }


void ADoor::LatchHoldTimeLineUpdate(float value)
{
	float lerpValue = FMath::Lerp(50, 0, value);
	LatchFront->SetRelativeRotation(FRotator(lerpValue, 0, 0));
	LatchBack->SetRelativeRotation(FRotator(lerpValue, 0, -180));
	
}

void ADoor::LatchHoldTimelineFinished() { }


void ADoor::HardClosingTimeLineUpdate(float value)
{
	float lerpValue = FMath::Lerp(CurrentRot.Yaw,InitialRot.Yaw, value);
	DoorItself->SetRelativeRotation(FRotator(0,lerpValue, 0));
}

void ADoor::HardClosingTimelineFinished()
{
	CurrentRot = DoorItself->GetRelativeRotation();
}