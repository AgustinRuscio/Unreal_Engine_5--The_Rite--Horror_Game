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

#define PRINTONVIEWPORT(X) GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT(X)));
#define END_KNOCKING_LOCATION CurrentRotation + FRotator(0, 3, 0)

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

//------------------------------------ Mesh Creation
	DoorItself = CreateDefaultSubobject<UStaticMeshComponent>("Door Itself");

	USceneComponent* NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NewRootComponent"));
	SetRootComponent(NewRootComponent);

	DoorItself->SetupAttachment(NewRootComponent);

	DoorItself->SetMobility(EComponentMobility::Movable);

	BaseFront = CreateDefaultSubobject<UStaticMeshComponent>("Front base");
	BaseBack = CreateDefaultSubobject<UStaticMeshComponent>("Back base");
	BaseBack->SetMobility(EComponentMobility::Movable);
	BaseFront->SetMobility(EComponentMobility::Movable);

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Key Mesh");
	KeyMesh->SetMobility(EComponentMobility::Movable);
	KeyMesh->SetupAttachment(DoorItself);
	KeyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	KeyMesh->SetVisibility(false);

	NumberMesh0 = CreateDefaultSubobject<UStaticMeshComponent>("Number Mesh");
	NumberMesh0->SetMobility(EComponentMobility::Movable);
	NumberMesh0->SetupAttachment(DoorItself);
	NumberMesh0->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	NumberMesh0->SetVisibility(false);

	NumberMesh1 = CreateDefaultSubobject<UStaticMeshComponent>("Number Mesh _ 1");
	NumberMesh1->SetMobility(EComponentMobility::Movable);
	NumberMesh1->SetupAttachment(DoorItself);
	NumberMesh1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	NumberMesh1->SetVisibility(false);

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

//--------------------------------------- Locked Widget 
	LockedWidget = CreateDefaultSubobject<ULockedWidget>("Locked Widget");
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Getter Methods
bool ADoor::IsLocked() const
{
	return bIsLocked;
}

//----------------------------------------------------------------------------------------------------------------------
bool ADoor::NeedKey() const
{
	return  bNeedKey;
}

//----------------------------------------------------------------------------------------------------------------------
bool ADoor::KeyUnlocked() const
{
	return bKeyUnlocked;
}
#pragma endregion 

//----------------------------------------------------------------------------------------------------------------------
void ADoor::Interaction()
{
	if(!bCanInteract) return;
	
	OnInteractionTrigger.Broadcast(this);

	CurrentYaw = GetActorRotation().Yaw;
	
	TutorialInteraction();
	
	CheckLocked();
	
	CheckPlayerForward();
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Action Methods
void ADoor::ObtainKey()
{
	bKeyUnlocked = true;

	if(SisterDoor != nullptr)
		SisterDoor->UnlockDooUnlockedFromSisterDoor();
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::UnlockDooUnlockedFromSisterDoor()
{
	bOpenFromSisterDoor = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::Open()
{
	bCanInteract	= false;
	bTimeLineOpen	= true;
	CurrentRotation = GetActorRotation();
	TimeLineOpenDoor.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::Close()
{
	bCanInteract	= false;
	bTimeLineOpen	= false;
	CurrentRotation = GetActorRotation();
	TimeLineOpenDoor.ReverseFromEnd();
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::HardClosing()
{
	UGameplayStatics::SpawnSoundAtLocation(this, SFXDoorSlam, GetActorLocation());
	TimeLineHardClosing.Play();
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::AutomaticClose()
{
	bCanInteract	= false;
	bTimeLineOpen	= false;
	CurrentRotation = GetActorRotation();
	TimeLineOpenDoor.ReverseFromEnd();
	UGameplayStatics::PlaySoundAtLocation(this, SFXDoorClinck, GetActorLocation());
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::ScaryKnock()
{
	bCanInteract = false;
	CurrentRotation = GetActorRotation();
	TimeLineScaryKnock.PlayFromStart();
	TimeLineLatchAnim.PlayFromStart();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SFXScaryKnocking, GetActorLocation());
}
#pragma endregion 

//----------------------------------------------------------------------------------------------------------------------
#pragma region Setter Methods
void ADoor::SetDoorKeyValues(FString itemName, PickableItemsID id)
{
	keyName = itemName;
	keyId = id;
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::SetCanDragState(bool newDragState)
{
	bcanDrag = newDragState;
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::SetLockedState(bool LockedNewState)
{
	bIsLocked = LockedNewState;
}
#pragma endregion 


//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	CreateWidgets();
	
	InitializeNeededValues();

	SetTutorialDoor();
	
	BindTimeLines();
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RunTimeLinesTick(DeltaTime);
	
	CheckCanSound(DeltaTime);

	HoldingTimerRunner(DeltaTime);

	bHolding = Player->IsHoldInteractBTN();
	
	CheckDragDoor();
	CheckIfLookingDoor();

	if (DEBUGGING)
	{
		//GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Orange, FString::Printf(TEXT("bHolding %d"), bHolding));
		//GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Orange, FString::Printf(TEXT("bcanDrag %d"), bcanDrag));

		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Orange, FString::Printf(TEXT("Max Rotation %f"), MaxYawrotation));
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Orange, FString::Printf(TEXT("Curretn Yaw %f"), CurrentYaw));
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(TutorialTimerHandle);
		GetWorldTimerManager().ClearTimer(UnlockedDoorTimerHandle);

		if(timerDelegateUnlockDoor.IsBound())
			timerDelegateUnlockDoor.Unbind();

		if (timerDelegateTutorial.IsBound())
			timerDelegateTutorial.Unbind();
	}
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Initializer Methods
void ADoor::CreateWidgets()
{
	LockedWidget = CreateWidget<ULockedWidget>(GetWorld(), LockedUI);
	LockedWidget->AddToViewport();
	LockedWidget->SetVisibility(ESlateVisibility::Hidden);
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::InitializeNeededValues()
{
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	FirstYawrotation = GetActorRotation().Yaw;
	MaxYawrotation = bFrontOpen ? FirstYawrotation + FrontAngle : FirstYawrotation - FrontAngle;
	
	InitialRot = GetActorRotation();
	CurrentRot = GetActorRotation();

	FRotator DoorRotation = GetActorRotation();
	FVector DooraForwardVector = GetActorLocation().RightVector;
	forward = DoorRotation.RotateVector(DooraForwardVector);
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region Tutorial Methods
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

//----------------------------------------------------------------------------------------------------------------------
void ADoor::TutorialInteraction()
{
	if(bIsTutorialDoor && !bDoOnceTut)
	{
		bDoOnceTut = true;
		TutorialWidget->SetVisibility(ESlateVisibility::Visible);
		
		if (!GetWorldTimerManager().IsTimerActive(TutorialTimerHandle))
		{
			timerDelegateTutorial.BindLambda([&]
			{
				TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
			});
			
			//GetWorldTimerManager().SetTimer(TutorialTimerHandle, timerDelegate, 2.f, false);
			GetWorldTimerManager().SetTimer(TutorialTimerHandle, this, &ADoor::HideTutorialWidget, 2.f, false);
		}
	}
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region Checker Methods
void ADoor::HoldingTimerRunner(float DeltaTime)
{
	bHolding ? DoorTimer += DeltaTime: DoorTimer = 0;
}

//----------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------
void ADoor::CheckPlayerForward()
{
	FVector DooraLocation = GetActorLocation();

	FVector PlayerLocation = Player->GetActorLocation();

	FVector PlayerDirection = PlayerLocation - DooraLocation;

	PlayerDirection.Normalize();
	
	float DotProduct = FVector::DotProduct(forward, PlayerDirection);

	if (DotProduct > 0.0f)
		bIsPlayerForward = true;
	else if (DotProduct < 0.0f)
		bIsPlayerForward = false;
}

//----------------------------------------------------------------------------------------------------------------------
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
					UnlockDoorWithKey();
				}
			}
			else if(bOpenFromSisterDoor)
			{
				UnlockDoorWithKey();
			}
			else
				ItsLocked();
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::CalculateRotation()
{
	float DoorFloat = Player->GetDoorFloat();
	float preSum = 0;

	if(LastYaw != 1604)
		CurrentYaw = LastYaw;
	
	if(bFrontOpen)
	{
		if(bIsPlayerForward)
		{
			preSum = CurrentYaw + DoorFloat * -1;
			
			if(preSum  >= MaxYawrotation)
				preSum = MaxYawrotation;
			else if(preSum <= FirstYawrotation)
				preSum = FirstYawrotation;

			CurrentYaw = preSum;
		}
		else
		{
			preSum = CurrentYaw+ DoorFloat;
			
			if(preSum >= MaxYawrotation)
				preSum = MaxYawrotation;
			else if(preSum <= FirstYawrotation)
				preSum = FirstYawrotation;

			
			CurrentYaw = preSum;
		}
	}
	else
	{
		if(bIsPlayerForward)
		{
			preSum = CurrentYaw + DoorFloat;
			
			if (preSum >= FirstYawrotation)
				preSum = FirstYawrotation;
			else if (preSum <= MaxYawrotation)
				preSum = MaxYawrotation;

			CurrentYaw = preSum;
		}
		else
		{
			preSum = CurrentYaw + DoorFloat * -1;
			
			if(preSum >= FirstYawrotation)
				preSum = FirstYawrotation;
			else if(preSum <= MaxYawrotation)
				preSum = MaxYawrotation;
			
			CurrentYaw = preSum;
		}
	}
	
	LastYaw = CurrentYaw;
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::CheckDragDoor()
{
	if(!bcanDrag || bIsLocked || (bNeedKey && !bKeyUnlocked))
		return;
	
	LatchHolding(bHolding);

	if(DoorTimer < DoorOpenOffsetCD) return;
	
	CalculateRotation();
	
	SetActorRotation(FRotator(GetActorRotation().Pitch, CurrentYaw, GetActorRotation().Roll));
}

//----------------------------------------------------------------------------------------------------------------------
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
	IgnoredActors.Add(Player);

	bool hit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End,
								 TEnumAsByte<ETraceTypeQuery>(ECollisionChannel::ECC_WorldDynamic),
								 false, IgnoredActors, EDrawDebugTrace::None,HitResult,false);
	
	//bool hit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End,
	//						 TEnumAsByte<ETraceTypeQuery>(ECollisionChannel::ECC_WorldDynamic),
	//						 false, IgnoredActors,
	//						EDrawDebugTrace::ForDuration,HitResult, false, FLinearColor::Red, FLinearColor::Green, 1.f);
	
	
	if(hit && HitResult.GetActor() == this)
	{		
		bIsLookingDoor = true;
		bWasLookingDoor = true;
		
		if(DEBUGGING)
			PRINTONVIEWPORT("Was looking")
		
		if(bHolding)
		{
			if(UE::Geometry::Distance(Player->GetActorLocation(), GetActorLocation()) > 500)
			{
				if(DEBUGGING)
					PRINTONVIEWPORT("Lejos")

				return;
			}

			if(DEBUGGING)
				PRINTONVIEWPORT("Looking and holding")

			Player->SetDraggingState(true, this);
			bcanDrag = Player->CheckCanDrag();
		}
		else
		{	
			Player->SetDraggingState(false, this);
			
			if(DEBUGGING)
				PRINTONVIEWPORT("Looking but no holding")
			
			bcanDrag = false;
			bWasLookingDoor = false;
		}
	}
	else
	{
		bIsLookingDoor = false;

		if(DEBUGGING)
			PRINTONVIEWPORT("Wasnt looking")
		
		if(bHolding)
		{
			if(bWasLookingDoor)
			{
				if(DEBUGGING)
					PRINTONVIEWPORT("Was holding when quit looking")
				
				Player->SetDraggingState(true,this);
				bcanDrag = Player->CheckCanDrag();
			}
		}
		else
		{
			if(DEBUGGING)
				PRINTONVIEWPORT("Wasten holding")
			
			Player->SetDraggingState(false, this);
			bcanDrag = false;
			bWasLookingDoor = false;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::UnlockDoorWithKey()
{
	if(SisterDoor != nullptr)
	{
		SisterDoor->SetCanDragState(false);
		SisterDoor->SetCanInteract(false);
	}

	bCanInteract = false;
	bcanDrag = false;
	bIsLocked = true;

	FirstTimeKeySound++;
	KeyMesh->SetVisibility(true);

	KeyStartLocation = Player->GetActorLocation();
	KeyEndLocation = KeyMesh->GetComponentLocation();

	Player->RemoveFromInventory(keyName ,keyId);

	TimeLineUnlockDoor.PlayFromStart();
}

#pragma endregion 

//----------------------------------------------------------------------------------------------------------------------
# pragma region FeedBack Methods
void ADoor::ItsLocked()
{
	if(IsValid(SFXVoiceLocked))
		Player->ForceTalk(SFXVoiceLocked);
	
	LockedWidget->SetVisibility(ESlateVisibility::Visible);
	LatchAnim();
	TimeLineItsLocked.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::LatchAnim()
{
	TimeLineLatchAnim.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::LatchHolding(bool isOppening)
{
	
	if(isOppening)
	{
		if(!bDoOnceOpenLatchAnim) return;
		
		if(bLatchPlay)
		{
			bDoOnceOpenLatchAnim = false;
			bLatchPlay = false;
			TimeLineLatchHold.PlayFromStart();
		}
	}
	else
	{
		if(bLatchReversePlay)
		{
			bLatchReversePlay = false;
			TimeLineLatchHold.ReverseFromEnd();
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::HideTutorialWidget()
{
	TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region TimeLines Methods
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

	//------- Unlock door timeline
	FOnTimelineFloat UnlockDoorTimelineTickCallback;
	UnlockDoorTimelineTickCallback.BindUFunction(this, FName("UnlockDoorTimeLineTick"));
	TimeLineUnlockDoor.AddInterpFloat(CurveUnlockDoor, UnlockDoorTimelineTickCallback);
	
	FOnTimelineEventStatic UnlockDoorTimelineFinishCallback;
	UnlockDoorTimelineFinishCallback.BindUFunction(this, FName("UnlockDoorTimeLineFinished"));
	TimeLineUnlockDoor.SetTimelineFinishedFunc(UnlockDoorTimelineFinishCallback);

	//------- Unlock door timeline
	FOnTimelineFloat ScaryKnockTimelineTickCallback;
	ScaryKnockTimelineTickCallback.BindUFunction(this, FName("ScaryKnockingTimeLineUpdate"));
	TimeLineScaryKnock.AddInterpFloat(ScaryKnockingCurve, ScaryKnockTimelineTickCallback);
	
	FOnTimelineEventStatic ScaryKnockTimelineFinishCallback;
	ScaryKnockTimelineFinishCallback.BindUFunction(this, FName("ScaryKnockingTimelineFinished"));
	TimeLineScaryKnock.SetTimelineFinishedFunc(ScaryKnockTimelineFinishCallback);
	
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::RunTimeLinesTick(float DeltaTime)
{
	TimeLineOpenDoor.TickTimeline(DeltaTime);
	TimeLineItsLocked.TickTimeline(DeltaTime);
	TimeLineLatchAnim.TickTimeline(DeltaTime);
	TimeLineHardClosing.TickTimeline(DeltaTime);
	TimeLineLatchHold.TickTimeline(DeltaTime);
	TimeLineUnlockDoor.TickTimeline(DeltaTime);
	TimeLineScaryKnock.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::OpenCloseTimeLineUpdate(float value)
{
	float newRot;

	if(bTimeLineOpen)
	{
		if(OpenRotation.Yaw == LastYaw)
			newRot = FMath::Lerp(LastYaw, OpenRotation.Yaw, value);
		else
			newRot = FMath::Lerp(CloseRotation.Yaw,OpenRotation.Yaw, value);
	}
	else
	{
		if(CloseRotation.Yaw == LastYaw)
			newRot = FMath::Lerp(CloseRotation.Yaw,OpenRotation.Yaw, value);
		else
			newRot = FMath::Lerp(CloseRotation.Yaw,LastYaw, value);
	}

	SetActorRotation(FRotator(GetActorRotation().Pitch, newRot, GetActorRotation().Roll));
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::OpenCloseTimelineFinished()
{
	LastYaw		 = GetActorRotation().Yaw;
	bCanInteract = true;
	
	CalculateRotation();
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::ItLockedTimeLineUpdate(float value)
{
	float TargetYaw = CloseRotation.Yaw + 5.0f;
	float NewYaw = FMath::Lerp(CloseRotation.Yaw, TargetYaw, value);

	SetActorRotation(FRotator(0, NewYaw, 0));
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::ItLockedTimelineFinished()
{
	UGameplayStatics::PlaySound2D(this, SFXDoorLocked);
	LockedWidget->SetVisibility(ESlateVisibility::Hidden);
	++AudioCounterItsLocked;
	
	CurrentRot = GetActorRotation();
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::LatchAnimTimeLineUpdate(float value)
{
	float lerpValue = FMath::Lerp(5, 50, value);
	LatchFront->SetRelativeRotation(FRotator(lerpValue, LatchFront->GetRelativeRotation().Yaw, LatchFront->GetRelativeRotation().Roll));
	LatchBack->SetRelativeRotation(FRotator(lerpValue, LatchBack->GetRelativeRotation().Yaw, LatchBack->GetRelativeRotation().Roll));
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::LatchAnimTimelineFinished() { }

//----------------------------------------------------------------------------------------------------------------------
void ADoor::LatchHoldTimeLineUpdate(float value)
{
	float lerpValue = FMath::Lerp(50, 0, value);
	LatchFront->SetRelativeRotation(FRotator(lerpValue, LatchFront->GetRelativeRotation().Yaw, LatchFront->GetRelativeRotation().Roll));
	LatchBack->SetRelativeRotation(FRotator(lerpValue, LatchBack->GetRelativeRotation().Yaw, LatchBack->GetRelativeRotation().Roll));
	//LatchBack->SetRelativeRotation(FRotator(lerpValue, 0, -180));
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::LatchHoldTimelineFinished()
{
	if(!bLatchPlay)
	{
		bLatchPlay = true;
	}

	if(!bLatchReversePlay)
	{
		bLatchReversePlay = true;
		bDoOnceOpenLatchAnim = true;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::HardClosingTimeLineUpdate(float value)
{
	float newRot = FMath::Lerp(CurrentRot.Yaw, CloseRotation.Yaw, value);
	
	LastYaw = newRot;
	SetActorRotation(FRotator(GetActorRotation().Pitch, newRot, GetActorRotation().Roll));
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::HardClosingTimelineFinished()
{
	CalculateRotation();
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::UnlockDoorTimeLineTick(float value)
{
	auto lerp = FMath::Lerp(KeyStartLocation, KeyEndLocation, value);
	KeyMesh->SetWorldLocation(lerp);
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::UnlockDoorTimeLineFinished()
{
	if(!GetWorld()->GetTimerManager().IsTimerActive(UnlockedDoorTimerHandle))
	{
		timerDelegateUnlockDoor.BindLambda([&]
		{
			bCanInteract = true;
			bcanDrag = true;
			
			bIsLocked = false;
			bKeyUnlocked = true;
			
			if(SisterDoor != nullptr)
			{
				SisterDoor->SetCanDragState(true);
				SisterDoor->bIsLocked = false;
				SisterDoor->bKeyUnlocked = true;
				SisterDoor->FirstTimeKeySound = 1;
				SisterDoor->SetCanInteract(true);
			}
			UGameplayStatics::SpawnSound2D(this, SFXDoorUnlocked);

			GetWorld()->GetTimerManager().ClearTimer(UnlockedDoorTimerHandle);
			
			if(bDisapearKey)
			{
				KeyMesh->SetVisibility(false);
			}
		});
		
		GetWorld()->GetTimerManager().SetTimer(UnlockedDoorTimerHandle, timerDelegateUnlockDoor, 1.5f, false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::ScaryKnockingTimeLineUpdate(float value)
{
	auto lerpLocation = FMath::Lerp(CurrentRotation, END_KNOCKING_LOCATION, value);
	SetActorRotation(lerpLocation);

	float lerpValue = FMath::Lerp(5, 50, value);
	LatchFront->SetRelativeRotation(FRotator(lerpValue, LatchFront->GetRelativeRotation().Yaw, LatchFront->GetRelativeRotation().Roll));
	LatchBack->SetRelativeRotation(FRotator(lerpValue, LatchBack->GetRelativeRotation().Yaw, LatchBack->GetRelativeRotation().Roll));
}

//----------------------------------------------------------------------------------------------------------------------
void ADoor::ScaryKnockingTimelineFinished()
{
	bCanInteract = true;
}
#pragma endregion
