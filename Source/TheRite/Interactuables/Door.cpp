#include "Door.h"

#include "Components/TimelineComponent.h"
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

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


void ADoor::CheckDragDoor()
{
	if(!bHolding || !bIsLookingDoor || bIsLocked || (bNeedKey && !bKeyUnlocked))
		return;

	float Yaw = DoorItself->GetRelativeRotation().Yaw;

	float Check = FMath::ClampAngle(Yaw, FrontAngle, (FrontAngle*-1));

	float DoorFloat = Player->GetDoorFloat();
	
	LatchHolding(bHolding);

	if(DoorTimer < DoorCD) return;
	
	if(Yaw != Check)
	{

		float YawRot = DoorFloat * Sensitivity;
		
		DoorItself->AddLocalRotation(FRotator(0, YawRot,0));
	}
	else
	{
		if(Yaw >= FrontAngle)
			DoorItself->SetRelativeRotation(FRotator(0,(FrontAngle-1),0));
		else
		{
			float num= FrontAngle * -1;
			
			DoorItself->SetRelativeRotation(FRotator(0,(num+1),0));
		}
	}
}

void ADoor::CheckIfLookingDoor()
{
	bHolding = Player->IsHoldInteracBTN();
	
	if(!bHolding) return;
	
	 FVector Start = Player->GetCamera()->GetComponentLocation();
	
	 FVector distace = Player->GetActorForwardVector() * 300;
	 FVector End = Start + distace;

	FHitResult HitResult;

	TArray<AActor*> IgnoredActors;

	bool hit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End,
								 TEnumAsByte<ETraceTypeQuery>(ECollisionChannel::ECC_WorldDynamic),
								 false, IgnoredActors,
								EDrawDebugTrace::ForDuration,HitResult, false);

	if(hit)
		bIsLookingDoor = HitResult.GetActor() == this;
	else
		bIsLookingDoor = false;
}

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


void ADoor::BeginPlay()
{
	Super::BeginPlay();

	BindTimeLines();
	
	InitialRot = DoorItself->GetRelativeRotation();
	CurrentRot = DoorItself->GetRelativeRotation();
	
	LockedWidget = CreateWidget<ULockedWidget>(GetWorld(), LockedUI);
	LockedWidget->AddToViewport();
	LockedWidget->SetVisibility(ESlateVisibility::Hidden);

	if(bIsTutorialDoor)
	{
		TutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), TutorialUI);
		TutorialWidget->AddToViewport();
		TutorialWidget->SetVisibility(ESlateVisibility::Hidden);

		auto controller = GetWorld()->GetFirstPlayerController();
	
		if(auto alexController = Cast<AAlexPlayerController>(controller))
		{
			alexController->OnKeyPressed.AddDynamic(TutorialWidget, &UTutorialWidget::SetKeyMode);
		}
		
	}
	
	Player = Cast<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeLineOpenDoor.TickTimeline(DeltaTime);
	TimeLineItsLocked.TickTimeline(DeltaTime);
	TimeLineLatchAnim.TickTimeline(DeltaTime);
	TimeLineHardClosing.TickTimeline(DeltaTime);
	TimeLineLatchHold.TickTimeline(DeltaTime);
	
	if(!bCanSoundItsLocked)
	{
		ItsLockedTimer+= DeltaTime;

		if(ItsLockedTimer > ItsLockedCD)
		{
			bCanSoundItsLocked = true;
			ItsLockedTimer = 0.0f;
		}
	}

	if(bHolding)
		DoorTimer += DeltaTime;
	else
		DoorTimer = 0;
	
	CheckDragDoor();
	CheckIfLookingDoor();
}

void ADoor::HideTutorial()
{
	TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ADoor::Interaction()
{
	if(bIsTutorialDoor && !bDoOnceTut)
	{
		bDoOnceTut = true;
		TutorialWidget->SetVisibility(ESlateVisibility::Visible);
		
		if (!GetWorldTimerManager().IsTimerActive(TutorialTimerHandle))
			GetWorldTimerManager().SetTimer(TutorialTimerHandle, this, &ADoor::HideTutorial, 2.f, false);
	}
	
	if(bFlipFlop)
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
					}
				}
				else
					ItsLocked();
			}
		}
	}
	else
	{
		if(bIsLocked)
			ItsLocked();
	}
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

void ADoor::ObteinKey()
{
	bKeyUnlocked = true;
}

bool ADoor::IsLocked() const
{
	return bIsLocked;
}

bool ADoor::NeedKey() const
{
	return  bNeedKey;
}

bool ADoor::KeyUnlocked() const
{
	return bKeyUnlocked;
}

void ADoor::SetLockedState(bool lockednewState)
{
	bIsLocked = lockednewState;
}

void ADoor::ItsLocked()
{
	if(IsValid(SFXVoiceLocked))
	{
		Player->ForceTalk(SFXVoiceLocked);
	}
	
	LockedWidget->SetVisibility(ESlateVisibility::Visible);
	LatchAnim();
	TimeLineItsLocked.PlayFromStart();
}

void ADoor::LatchAnim()
{
	TimeLineLatchAnim.PlayFromStart();
}

void ADoor::AutomaticClose()
{
	TimeLineOpenDoor.ReverseFromEnd();
	UGameplayStatics::PlaySoundAtLocation(this, SFXDoorClinck, GetActorLocation());
}

void ADoor::LatchHolding(bool isOppening)
{
	if(isOppening)
		TimeLineLatchHold.PlayFromStart();
	else
		TimeLineLatchHold.ReverseFromEnd();
}
