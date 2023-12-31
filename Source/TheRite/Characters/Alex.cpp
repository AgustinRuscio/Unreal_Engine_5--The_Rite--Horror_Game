#include "Alex.h"

#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Widgets/CenterDotWidget.h"

AAlex::AAlex()
{
 	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	
	BodyLight = CreateDefaultSubobject<UPointLightComponent>("Body Light");
	
	Hint = CreateDefaultSubobject<UChildActorComponent>("Hint");
	Hint->SetupAttachment(GetMesh(), "hand_l");
	
	Lighter = CreateDefaultSubobject<UChildActorComponent>("Ligher");
	FlamePlane =  CreateDefaultSubobject<UStaticMeshComponent>("Plane Lighter");
	LighterLight = CreateDefaultSubobject<UPointLightComponent>("Lighter Light");

	Lighter->SetupAttachment(GetMesh(), "hand_r");
	LighterLight->SetupAttachment(Lighter);
	FlamePlane->SetupAttachment(Lighter);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	ScreamerSkeleton = CreateDefaultSubobject<USkeletalMeshComponent>("Screammer Skeleton");

	TempAudio = CreateDefaultSubobject<UAudioComponent>("TempAudio");
	
	Camera->SetupAttachment(GetMesh());
	ScreamerSkeleton->SetupAttachment(Camera);
}

void AAlex::OnJumpScare()
{
	DisableInput(MyController);
	ScreamerSkeleton->SetVisibility(true);
	ScreamerSkeleton->PlayAnimation(ScreamerAnim,false);
	
	if (!GetWorldTimerManager().IsTimerActive(ScreamerTimerHanlde))
		GetWorldTimerManager().SetTimer(ScreamerTimerHanlde, this, &AAlex::TimeOver, 1.2f, false);

}

void AAlex::TimeOver()
{
	EnableInput(MyController);
	ScreamerSkeleton->SetVisibility(false);
}

void AAlex::MakeTalk()
{
	bCanTalk = false;
	
	TempAudio = UGameplayStatics::SpawnSound2D(this, TalkSound);
	TempAudio->OnAudioFinished.AddDynamic(this, &AAlex::OnAudioFinished);
}

void AAlex::OnAudioFinished()
{
	bCanTalk = true;
	TempAudio = nullptr;
}

void AAlex::StopTalking()
{
	if(TempAudio!=nullptr)
		TempAudio->Stop();
}

void AAlex::CreateWidgets()
{
	PuaseWidget = CreateWidget<UPauseMenuWidget>(GetWorld(),PauseMenu);
	PuaseWidget->AddToViewport(0);
	PuaseWidget->SetVisibility(ESlateVisibility::Hidden);
	PuaseWidget->SetIsFocusable(true);

	DotWidget = CreateWidget<UCenterDotWidget>(GetWorld(),DotUI);
	DotWidget->AddToViewport(-1);
	DotWidget->SetVisibility(ESlateVisibility::Visible);
}

void AAlex::ForceTalk(USoundBase* Voice)
{
	if(!bCanTalk)
		StopTalking();

	TalkSound = Voice;
	MakeTalk();
}

bool AAlex::IsHoldInteracBTN() const
{
	return bHoldingInteractBTN;
}

float AAlex::GetDoorFloat() const
{
	return DoorFloat;
}

UCameraComponent* AAlex::GetCamera() const
{
	return Camera;
}

void AAlex::BeginPlay()
{
	Super::BeginPlay();
	
	CreateWidgets();
	LighterLight->SetVisibility(false);

	OnLighterAnimMontage.AddDynamic(this, &AAlex::MontageAnimOnOff);

	BindTimeLineMethods();
	//BindActions();
}

void AAlex::BindTimeLineMethods()
{
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("CameraTargetTick"));
	TargetCameraTimeLine.AddInterpFloat(EmptyCurve, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("CameraTargetFinished"));
	TargetCameraTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

void AAlex::CameraTargeting(FVector Target)
{
	CameraLookTarget = Target;
	TargetCameraTimeLine.PlayFromStart();
}

void AAlex::CameraTargetTick(float time)
{
	FRotator targetParam =  UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CameraLookTarget);
	
	FRotator NewRotator = FMath::RInterpTo(MyController->GetControlRotation(),targetParam, GetWorld()->DeltaTimeSeconds, 2.0f);
	
	MyController->SetControlRotation(NewRotator);
}

void AAlex::CameraTargetFinished()
{
	CameraLookTarget = FVector::Zero();
}


//------------------------ Inputs Actions
void AAlex::BindActions()
{
	MyController = Cast<AAlexPlayerController>(Controller);
	MyController->OnPlayerMovement.AddDynamic(this, &AAlex::MovePlayer);
	
	MyController->OnCameraMoved.AddDynamic(this, &AAlex::MoveCamera);
	
	MyController->OnStartSprint.AddDynamic(this, &AAlex::StartSprint);
	MyController->OnStopSprint.AddDynamic(this, &AAlex::StopSprint);
	
	MyController->OnLighter.AddDynamic(this, &AAlex::TurnLigherIfPossible);
	
	MyController->OnInteractionPressed.AddDynamic(this, &AAlex::Interaction);
	MyController->OnHoldingBtn.AddDynamic(this, &AAlex::CheckHolding);
	
	MyController->OnOpenHint.AddDynamic(this, &AAlex::OpenHint);
	MyController->OnCloseHint.AddDynamic(this, &AAlex::CloseHint);
	
	MyController->OnPause.AddDynamic(this, &AAlex::OpenPause);
}

void AAlex::MovePlayer(FVector2D vector)
{
	const FRotator moveRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

	if(vector.X > 0.05f || vector.X < -0.05f)
	{
		const FVector directionVector = moveRotation.RotateVector(FVector::RightVector);
		AddMovementInput(directionVector,vector.X);
	}

	if(vector.Y > 0.05f || vector.Y < -0.05f)
	{
		const FVector directionVector = moveRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(directionVector, vector.Y);
	}
}

void AAlex::MoveCamera(FVector2D vector)
{
	AddControllerYawInput(vector.X);
	AddControllerPitchInput(vector.Y);
	DoorFloat = vector.X;
}


void AAlex::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AAlex::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}


void AAlex::TurnLigherIfPossible()
{
	if(!bCanUseLigher) return;
	
	CheckLighterOn();
}

void AAlex::CheckLighterOn()
{
	if(!bLighter)
	{
		if(bLighterOnCD)
		{
			UGameplayStatics::SpawnSound2D(this, LighterOn);
			bLighter = true;
			LighterLight->SetVisibility(true);
			OnLighterAnimMontage.Broadcast();
		}
		else
		{
			if(!bCanSound) return;
			
			UGameplayStatics::SpawnSound2D(this, LighterCDSound);
			bCanSound = false;
			bLighter = false;
			LighterLight->SetVisibility(false);
			OnLighterAnimMontage.Broadcast();
		}
	}
	else
	{
		bLighter = false;
		LighterLight->SetVisibility(false);
		OnLighterAnimMontage.Broadcast();
	}
}


void AAlex::Interaction()
{
	if(!bCanTalk || !bCanInteract) return;
	
	if(TalkSound != nullptr)
		MakeTalk();

	ActualInteractuable->Interaction();
}

void AAlex::CheckHolding(bool IsHolding)
{
	bHoldingInteractBTN = IsHolding;
}


void AAlex::OpenHint()
{
	if(!bHasHint) return;

	PlayAnimMontage(HintAnimMontage);
	Hint->SetVisibility(true);
}

void AAlex::CloseHint()
{
	if(!bHasHint) return;

	StopAnimMontage(HintAnimMontage);
	Hint->SetVisibility(false);
}


void AAlex::OpenPause()
{
	if(bPauseFlip)
	{
		PuaseWidget->SetVisibility(ESlateVisibility::Visible);
		PuaseWidget->SetUserFocus(MyController);
		bPauseFlip = false;
	}
	else
	{
		PuaseWidget->SetVisibility(ESlateVisibility::Hidden);
		bPauseFlip = true;
	}
	
	MyController->SetPauseGame(!bPauseFlip);
}

//-----------------------------------------------

void AAlex::MontageAnimOnOff()
{
	if(bLighter)
	{
		PlayAnimMontage(LighterMontage);
		LighterLight->SetVisibility(true);
		FlamePlane->SetVisibility(true);
	}
	else
	{
		StopAnimMontage(LighterMontage);
		LighterLight->SetVisibility(false);
		FlamePlane->SetVisibility(false);
	}
}

void AAlex::LighterSoundTimer(float deltaTime)
{
	AudioTimer = AudioTimer+deltaTime;
	
	if(AudioTimer < 2.05f)
		return;

	bCanSound = true;
	AudioTimer = 0;
}

void AAlex::CheckLighterCooldDown(float deltaTime)
{
	if(bLighterOnCD)
	{
		LighterTimer += deltaTime;
		
		if(LighterTimer >= LighterCD)
		{
			bLighterOnCD = false;
			LighterTimer = 0;
		}
		else
			LighterTimer = LighterTimer <= 0 ? 0 : LighterTimer - deltaTime;
	}
	else
	{
		if(bLighter)
		{
			LighterTimer += deltaTime;

			if(LighterTimer < MaxLighterTime) return;

			bLighter = false;
			LighterLight->SetVisibility(false);
			bLighterOnCD = true;
			OnLighterAnimMontage.Broadcast();
		}
		else
			LighterTimer = LighterTimer <= 0 ? 0 : LighterTimer - deltaTime;
	}
}

void AAlex::HeadBob()
{
	if(GetVelocity().Length() > 0)
	{
		if(GetVelocity().Length() < 700)
			MyController->ClientStartCameraShake(CameraShakeWalk);
		else
			MyController->ClientStartCameraShake(CameraShakeRun);
	}
	else
		MyController->ClientStartCameraShake(CameraShakeIdle);
}

void AAlex::Breath(float deltaTime)
{
	if(BreathTimer > 15)
	{
		UGameplayStatics::PlaySound2D(this, BreathSound);
		BreathTimer = 0;
	}
	else
		BreathTimer = BreathTimer + deltaTime;
}

void AAlex::InteractuableCheck()
{
	if(!bCanTalk)
	{
		DotWidget->Interact(false, false,true);
	}
	else
	{
		FVector Start = Camera->GetComponentToWorld().GetLocation();

		FVector rot = Camera->GetComponentToWorld().GetRotation().GetForwardVector() * RangeInteractuable;
		FVector End = Start + rot;

		TArray<AActor*> IgnoredActors;
		IgnoredActors.Add(this);

		FHitResult OutHit;
		
		UKismetSystemLibrary::SphereTraceSingle(this,Start,End,7.5f,ETraceTypeQuery::TraceTypeQuery1,
								false,IgnoredActors,EDrawDebugTrace::None, OutHit, true);

		IIInteractuable* currentCheck = Cast<IIInteractuable>(OutHit.GetActor());

		if(!currentCheck)
		{
			ActualInteractuable = nullptr;
			TalkSound = nullptr;
			bCanInteract = false;
			
			DotWidget->Interact(true, false,false);
		}
		else
		{
			ActualInteractuable = currentCheck;
			TalkSound = ActualInteractuable->GetSound();

			if(IsDoorCheck(ActualInteractuable))
			{
				if(bDoorWasLocked)
				{
					bCanInteract = true;
					DotWidget->Interact(false, true,false);
				}
				else
				{
					bCanInteract = true;
					DotWidget->Interact(false, false,false);
				}
			}
			else
			{
				bCanInteract = true;
				DotWidget->Interact(false, false,false);
			}
		}
	}
}

bool AAlex::IsDoorCheck(IIInteractuable* checked)
{
	ADoor* currentCheck = Cast<ADoor>(checked);

	if(!currentCheck)
	{
		DoorChecked = nullptr;
		return false;
	}
	else
	{
		DoorChecked = currentCheck;

		if(DoorChecked->IsLocked())
		{
			bDoorWasLocked = true;
			return true;
		}
		else
		{
			if(DoorChecked->NeedKey())
			{
				if(DoorChecked->KeyUnlocked())
				{
					bDoorWasLocked = false;
					return true;
				}
				else
				{
					bDoorWasLocked = true;
					return true;
				}
			}
			else
			{
				bDoorWasLocked = false;
				return true;
			}
		}
	}
}

void AAlex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TargetCameraTimeLine.TickTimeline(DeltaTime);

	LighterSoundTimer(DeltaTime);
	CheckLighterCooldDown(DeltaTime);
	HeadBob();
	Breath(DeltaTime);
	InteractuableCheck();
}

void AAlex::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	MyController = Cast<AAlexPlayerController>(Controller);

	MyController->OnPlayerMovement.AddDynamic(this, &AAlex::MovePlayer);
	
	MyController->OnCameraMoved.AddDynamic(this, &AAlex::MoveCamera);
	
	MyController->OnStartSprint.AddDynamic(this, &AAlex::StartSprint);
	MyController->OnStopSprint.AddDynamic(this, &AAlex::StopSprint);
	
	MyController->OnLighter.AddDynamic(this, &AAlex::TurnLigherIfPossible);
	
	MyController->OnInteractionPressed.AddDynamic(this, &AAlex::Interaction);
	MyController->OnHoldingBtn.AddDynamic(this, &AAlex::CheckHolding);
	
	MyController->OnOpenHint.AddDynamic(this, &AAlex::OpenHint);
	MyController->OnCloseHint.AddDynamic(this, &AAlex::CloseHint);
	
	MyController->OnPause.AddDynamic(this, &AAlex::OpenPause);
}

void AAlex::CallPauseFunc()
{
	OpenPause();
}
