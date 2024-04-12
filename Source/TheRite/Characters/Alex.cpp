//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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

	TimerComponentForLighterDisplay = CreateDefaultSubobject<UTimerActionComponent>("Timer");
	
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	
	BodyLight = CreateDefaultSubobject<UPointLightComponent>("Body Light");
	
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
	APlayerController* PlayerController = Cast<APlayerController>(MyController);
    
	MyController->DisableInput(PlayerController);
	ScreamerSkeleton->SetVisibility(true);
	ScreamerSkeleton->PlayAnimation(ScreamerAnim,false);
	
	if (!GetWorldTimerManager().IsTimerActive(ScreamerTimerHanlde))
		GetWorldTimerManager().SetTimer(ScreamerTimerHanlde, this, &AAlex::TimeOver, .7f, false);

}

void AAlex::ForceDisableInput()
{
	APlayerController* PlayerController = Cast<APlayerController>(MyController);
    
	MyController->DisableInput(PlayerController);
}

void AAlex::ForceEnableInput()
{
	APlayerController* PlayerController = Cast<APlayerController>(MyController);
    
	MyController->EnableInput(PlayerController);
}

void AAlex::TimeOver()
{
	APlayerController* PlayerController = Cast<APlayerController>(MyController);
	OnJumpscaredFinished.Broadcast();
	ScreamerSkeleton->SetVisibility(false);
	MyController->EnableInput(PlayerController);
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
	PauseWidget = CreateWidget<UPauseMenuWidget>(GetWorld(),PauseMenu);
	PauseWidget->AddToViewport(0);
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	PauseWidget->SetIsFocusable(true);

	DotWidget = CreateWidget<UCenterDotWidget>(GetWorld(),DotUI);
	DotWidget->AddToViewport(-1);
	DotWidget->SetVisibility(ESlateVisibility::Visible);
	
	InventoryWidget = CreateWidget<UInventory>(GetWorld(),InventoryMenu);
	InventoryWidget->AddToViewport(0);
	InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidget->SetIsFocusable(true);

	OpenInventoryWidget = CreateWidget<UOpenInventory>(GetWorld(), OpenInventoryMenu);
	OpenInventoryWidget->AddToViewport(0);
	OpenInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	OpenInventoryWidget->SetIsFocusable(true);

	LighterReminderWidget = CreateWidget<UTutorialWidget>(GetWorld(), LighterRecordatoryMenu);
	LighterReminderWidget->AddToViewport(0);
	LighterReminderWidget->SetVisibility(ESlateVisibility::Hidden);
	LighterReminderWidget->SetIsFocusable(true);
	
	
	MyController->OnNextInventoryItem.AddDynamic(InventoryWidget, &UInventory::ShowNextItem);
	MyController->OnPrevInventoryItem.AddDynamic(InventoryWidget, &UInventory::ShowPrevItem);

	MyController->OnKeyPressed.AddDynamic(OpenInventoryWidget,  &UOpenInventory::SetKeyMode);
	MyController->OnKeyPressed.AddDynamic(LighterReminderWidget,  &UOpenInventory::SetKeyMode);
}

void AAlex::SetPlayerStats(bool canRun, bool canUseLighter)
{
	bCanRun = canRun;
	SetCanUseLigherState(canUseLighter);
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

bool AAlex::CheckCanDrag() const
{
	return bIsDragging;
}

float AAlex::GetDoorFloat() const
{
	return DoorFloat;
}

void AAlex::SetHintState(bool newHintState)
{
	bHasHint = newHintState;
}

void AAlex::SetCanUseLigherState(bool lighterState)
{
	bCanUseLigher = lighterState;
}

void AAlex::ForceTurnLighterOn()
{
	bLighter = true;
	CheckLighterOn();
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

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
	OnLighterAnimMontage.AddDynamic(this, &AAlex::MontageAnimOnOff);

	auto detector = GetWorld()->SpawnActor(DetectorSubclass);
	WrittingsDetector = CastChecked<AWrittingsDetector>(detector);
	WrittingsDetector->AttachToActor(Lighter->GetChildActor(), FAttachmentTransformRules::KeepRelativeTransform);
	WrittingsDetector->SetComponentSettings(LighterLight->SourceRadius, LighterLight->GetRelativeTransform());
	
	BindTimeLineMethods();


	if(bCanUseLigher)
		TimerComponentForLighterDisplay->TimerReach.AddDynamic(this, &AAlex::ShowLighterReminder);
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
}

void AAlex::DoorMovement(FVector2D vector)
{
	DoorFloat = vector.X;
}

void AAlex::SetDraggingState(bool shouldCheck)
{
	if(!bInventoryFlip) return;
	
	if(shouldCheck)
		bIsDragging = bHoldingInteractBTN;
	else
		bIsDragging = false;
	
	MyController->SetDoorMode(bIsDragging);
}

void AAlex::StartSprint()
{
	if(!bCanRun) return;
	
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AAlex::StopSprint()
{
	if(!bCanRun) return;
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
		if(!bLighterOnCD)
		{
			
			UGameplayStatics::SpawnSound2D(this, LighterOn);
			bLighter = true;

			
			SetLighterAssetsVisibility(true);
			
			OnLighterAnimMontage.Broadcast();
		}
		else
		{
			if(!bCanSound) return;
			
			UGameplayStatics::SpawnSound2D(this, LighterCDSound);
			bCanSound = false;
			bLighter = false;
			
			
			SetLighterAssetsVisibility(false);
			
			OnLighterAnimMontage.Broadcast();
		}
	}
	else
	{
		bLighter = false;
		
		SetLighterAssetsVisibility(false);
		
		OnLighterAnimMontage.Broadcast();
	}
}

void AAlex::SetCameraStun(bool stun)
{
	bStun = stun;
}

void AAlex::Interaction()
{
	if(!bCanTalk || !bCanInteract) return;
	
	if(TalkSound != nullptr)
		MakeTalk();

	ActualInteractuable->Interaction();
	
	if(ActualInteractuable->IsPickable())
	{
		InventoryWidget->AddItemToInventory(ActualInteractuable->GetItemName(), ActualInteractuable->GetItemID());

		OpenInventoryWidget->SetVisibility(ESlateVisibility::Visible);
		
		if (!GetWorldTimerManager().IsTimerActive(OpeninventorywidgetTimerHandle))
			GetWorldTimerManager().SetTimer(OpeninventorywidgetTimerHandle, this, &AAlex::CloseOpenInventoryWidget, 1.5f, false);
	}
}

void AAlex::CloseOpenInventoryWidget()
{
	OpenInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AAlex::CheckHolding(bool IsHolding)
{
	bHoldingInteractBTN = IsHolding;
}

void AAlex::OpenPause()
{
	if(bPauseFlip)
	{
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
		bPauseFlip = false;
	}
	else
	{
		PauseWidget->SetVisibility(ESlateVisibility::Hidden);
		bPauseFlip = true;
	}
	
	MyController->SetPauseGame(!bPauseFlip);
}

void AAlex::OpenInventory()
{
	if(bInventoryFlip)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		bInventoryFlip = false;
		InventoryWidget->OnInventoryOpen();
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		bInventoryFlip = true;
		InventoryWidget->OnInventoryClose();
	}
	
	MyController->SetUIOnly(!bInventoryFlip);
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
			
			SetLighterAssetsVisibility(false);
			
			bLighterOnCD = true;
			OnLighterAnimMontage.Broadcast();
		}
		else
			LighterTimer = LighterTimer <= 0 ? 0 : LighterTimer - deltaTime;
	}

}

void AAlex::ShowLighterReminder()
{
	LighterReminderWidget->SetVisibility(ESlateVisibility::Visible);

	if (!GetWorldTimerManager().IsTimerActive(LighterReminderTimer))
		GetWorldTimerManager().SetTimer(LighterReminderTimer, this, &AAlex::HideLighterReminder, 4.f, false);
}

void AAlex::HideLighterReminder()
{
	LighterReminderWidget->SetVisibility(ESlateVisibility::Hidden);
	TimerComponentForLighterDisplay->ActionFinished();
}

void AAlex::SetLighterAssetsVisibility(bool visibilityState)
{
	LighterLight->SetVisibility(visibilityState);
	Lighter->SetVisibility(visibilityState);
	FlamePlane->SetVisibility(visibilityState);
	WrittingsDetector->SetInteractionStatus(visibilityState);
}


void AAlex::HeadBob()
{
	if(bStun)
	{
		MyController->ClientStartCameraShake(CameraShakeStun);
	}
	else
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
	
}

void AAlex::InteractuableCheck()
{
	if(!bCanTalk)
	{
		DotWidget->Interact(false, false,true, false);
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
			
			DotWidget->Interact(true, false,false, false);
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
						DotWidget->Interact(false, true,false, currentCheck->IsMainItem());
					}	
					else
					{
						bCanInteract = true;
						DotWidget->Interact(false, false,false, currentCheck->IsMainItem());
					}
				}
				else
				{
					bCanInteract = true;
					DotWidget->Interact(false, false,false, currentCheck->IsMainItem());
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
	InteractuableCheck();
}

void AAlex::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	MyController = Cast<AAlexPlayerController>(Controller);

	MyController->OnPlayerMovement.AddDynamic(this, &AAlex::MovePlayer);
	
	MyController->OnCameraMoved.AddDynamic(this, &AAlex::MoveCamera);
	MyController->OnCameraMovedDoor.AddDynamic(this, &AAlex::DoorMovement);
	
	MyController->OnStartSprint.AddDynamic(this, &AAlex::StartSprint);
	MyController->OnStopSprint.AddDynamic(this, &AAlex::StopSprint);
	
	MyController->OnLighter.AddDynamic(this, &AAlex::TurnLigherIfPossible);
	
	MyController->OnInteractionPressed.AddDynamic(this, &AAlex::Interaction);
	MyController->OnHoldingBtn.AddDynamic(this, &AAlex::CheckHolding);
	
	MyController->OnPause.AddDynamic(this, &AAlex::OpenPause);
	MyController->OnInventory.AddDynamic(this, &AAlex::OpenInventory);
}

void AAlex::CallPauseFunc()
{
	OpenPause();
}