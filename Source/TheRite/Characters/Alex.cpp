//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Alex.h"
#include "MathUtil.h"
#include "Components/AudioComponent.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Components/TimerActionComponent.h"
#include "TheRite/Interactuables/IInteractuable.h"
#include "TheRite/Triggers/WrittingsDetector.h"
#include "TheRite/Widgets/CenterDotWidget.h"
#include "TheRite/Widgets/Inventory.h"
#include "TheRite/Widgets/OpenInventory.h"
#include "TheRite/Widgets/PauseMenuWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "TheRite/Interactuables/Door.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TheRite/Widgets/TutorialWidget.h"

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
	
	SpringArm_Lighter = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Lighter");
	SpringArm_Lighter->SetupAttachment(GetMesh(), "hand_r");
	
	Lighter->SetupAttachment(SpringArm_Lighter);
	LighterLight->SetupAttachment(Lighter);
	FlamePlane->SetupAttachment(Lighter);
	
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	ScreamerSkeleton = CreateDefaultSubobject<USkeletalMeshComponent>("Screammer Skeleton");

	TempAudio = CreateDefaultSubobject<UAudioComponent>("TempAudio");
	
	BodyLight->SetupAttachment(Camera);
	Camera->SetupAttachment(GetMesh());
	ScreamerSkeleton->SetupAttachment(Camera);
}

//---------------- Getter Methods
bool AAlex::IsHoldInteractBTN() const
{
	return bHoldingInteractBTN;
}

bool AAlex::CheckCanDrag() const
{
	return bIsDragging;
}

bool AAlex::GetFocusingState() const
{
	return bFocusing;
}

float AAlex::GetDoorFloat() const
{
	return DoorFloat;
}

float AAlex::GetInteractionRange() const
{
	return RangeInteractuable;
}

UCameraComponent* AAlex::GetCamera() const
{
	return Camera;
}

//---------------- System Class Methods
void AAlex::BeginPlay()
{
	Super::BeginPlay();
	
	CreateWidgets();
	LighterLight->SetVisibility(false);

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
	OnLighterAnimMontage.AddDynamic(this, &AAlex::MontageAnimOnOff);
	
	CreateWritingDetector();
	
	BindTimeLineMethods();
	
	if(bCanUseLigher && bShowLighterReminder)
		TimerComponentForLighterDisplay->TimerReach.AddDynamic(this, &AAlex::ShowLighterReminder);
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

void AAlex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TargetCameraTimeLine.TickTimeline(DeltaTime);
	FocusCameraTimeLine.TickTimeline(DeltaTime);
	
	LighterSoundTimer(DeltaTime);
	CheckLighterCooldDown(DeltaTime);
	HeadBob();
	InteractableCheck();
}

//---------------- Action Methods
void AAlex::CameraTargeting(FVector Target)
{
	CameraLookTarget = Target;
	TargetCameraTimeLine.PlayFromStart();
}

void AAlex::ForceTalk(USoundBase* Voice)
{
	if(!bCanTalk)
		StopTalking();

	TalkSound = Voice;
	MakeTalk();
}

void AAlex:: CallPauseFunc()
{
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);

	bPauseFlip = true;
	MyController->SetPauseGame(false);
}

void AAlex::ForceEnableInput()
{
	APlayerController* PlayerController = Cast<APlayerController>(MyController);
    
	MyController->EnableInput(PlayerController);
}
void AAlex::ForceDisableInput()
{
	APlayerController* PlayerController = Cast<APlayerController>(MyController);
    
	MyController->DisableInput(PlayerController);
}

void AAlex::ForceTurnLighterOn()
{
	bLighter = true;
	CheckLighterOn();
}

void AAlex::ForceLighterOff()
{
	SetLighterAssetsVisibility(false);
	bLighter = false;
	MontageAnimOnOff();
}

void AAlex::OnJumpScare()
{
	APlayerController* PlayerController = Cast<APlayerController>(MyController);
    
	MyController->DisableInput(PlayerController);
	ScreamerSkeleton->SetVisibility(true);
	ScreamerSkeleton->PlayAnimation(ScreamerAnim,false);
	
	if (!GetWorldTimerManager().IsTimerActive(TimerHandle_Screamer))
	{
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([&]
		{
			APlayerController* Controller = Cast<APlayerController>(MyController);
			OnJumpscaredFinished.Broadcast();
			ScreamerSkeleton->SetVisibility(false);
			MyController->EnableInput(Controller);
		});
		
		GetWorldTimerManager().SetTimer(TimerHandle_Screamer, timerDelegate, .7f, false);
	}
}

void AAlex::RemoveFromInventory(FString itemName, PickableItemsID id)
{
	InventoryWidget->RemoveItem(itemName, id);

	ConsumibleItemWidget->SetChangingText(FText::FromString(itemName + " used"));
	ConsumibleItemWidget->SetVisibility(ESlateVisibility::Visible);
	
	if (!GetWorldTimerManager().IsTimerActive(TimerHandle_ConsumableWidget))
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([&]
		{
			ConsumibleItemWidget->SetVisibility(ESlateVisibility::Hidden);
		});

		//GetWorldTimerManager().SetTimer(TimerHandle_ConsumableWidget, TimerDelegate, 2.f, false);
		GetWorldTimerManager().SetTimer(TimerHandle_ConsumableWidget, this, &AAlex::HideConsumableWidget, 2.f, false);
	}
}

//---------------- Setter Methods
void AAlex::SetPlayerOptions(bool canRun, bool canUseLighter, bool showLighterReminder)
{
	bCanRun = canRun;
	SetCanUseLighterState(canUseLighter);
	bShowLighterReminder = showLighterReminder;
}

void AAlex::SetCanUseLighterState(bool lighterState)
{
	bCanUseLigher = lighterState;
}

void AAlex::SetDraggingState(bool shouldCheck, ADoor* door)
{
	if(!bInventoryFlip || bFocus || bFocusing || bOnEvent)
		return;
	
	if(shouldCheck)
		bIsDragging = bHoldingInteractBTN;
	else
		bIsDragging = false;

		
	if(DoorChecked != door)
	{
		door->SetCanDragFalse();
	}
	
	MyController->SetDoorMode(bIsDragging);
}

void AAlex::SetCameraStun(bool stun)
{
	bStun = stun;
}

void AAlex::SetEventMode(bool onOff, float minX = 0, float maxX = 0, float minY= 0, float maxY= 0)
{
	auto camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	bOnEvent = onOff;
	
	if(onOff)
	{
		//bOnEvent = true;
		MyController->SetEventInput();

		VectorX.X = camera->ViewYawMax;
		VectorX.Y = camera->ViewYawMin;
		VectorY.Y = camera->ViewPitchMin;
		VectorY.X = camera->ViewPitchMax;
		
		
		camera->ViewYawMax = maxX;
		camera->ViewYawMin = minX;
		camera->ViewPitchMax = maxY;
		camera->ViewPitchMin = minY;
	}
	else
	{
		//bOnEvent = false;
		MyController->SetNormalInput();

		camera->ViewYawMax = VectorX.X;
		camera->ViewYawMin = VectorX.Y;
		camera->ViewPitchMin = VectorY.Y;
		camera->ViewPitchMax = VectorY.X;
	}
}

void AAlex::ForceHolding(bool newHolding)
{
	bHoldingInteractBTN = newHolding;
}

//----------------- View Methods
void AAlex::BackToNormalView(FTransform FromTransform, FVector ExitingVector, FRotator ExitingRotation)
{
	bFocus = false;
	SetActorLocation(FVector(FromTransform.GetLocation().X + ExitingVector.X, FromTransform.GetLocation().Y + ExitingVector.Y, GetActorLocation().Z + ExitingVector.Z));
	SetActorRotation(ExitingRotation);
	Rot = ExitingRotation;
	
	Camera->RemoveFromRoot();
	bFocusing = true;
	FocusCamTransform = FromTransform;
	
	FocusCameraTimeLine.ReverseFromEnd();
	
	AltarWidget->SetVisibility(ESlateVisibility::Hidden);
	DotWidget->SetVisibility(ESlateVisibility::Visible);
}

void AAlex::OnFocusMode(FTransform newTransform, FRotator ExitingRotation)
{
	ForceLighterOff();
	
	bFocus = true;
	bFocusing = true;

	Camera->bUsePawnControlRotation = false;

	MyController->OnCameraMoved.RemoveDynamic(this, &AAlex::MoveCamera);
	
	LastCamTransform = Camera->GetComponentTransform();
	FocusCamTransform = newTransform;
	
	FocusCameraTimeLine.PlayFromStart();

	AltarWidget->SetVisibility(ESlateVisibility::Visible);
	DotWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AAlex::MoveCamera(FVector NewCameraPos)
{
	Camera->SetWorldLocation(NewCameraPos);
}

void AAlex::MakeCameraView(FRotator Rotta)
{
	MyController->SetControlRotation(Rotta);
}

//---------------- Checker Methods
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

void AAlex::CheckHolding(bool IsHolding)
{
	if(bFocusing  || bFocus) return;
				
	bHoldingInteractBTN = IsHolding;
}

void AAlex::InteractableCheck()
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

		if(!currentCheck || !currentCheck->GetCanInteract())
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

//---------------- Initialization Methods
void AAlex::CreateWritingDetector()
{
	WrittingsDetector = CastChecked<AWrittingsDetector>(GetWorld()->SpawnActor(DetectorSubclass));
	WrittingsDetector->AttachToActor(Lighter->GetChildActor(), FAttachmentTransformRules::KeepRelativeTransform);
	WrittingsDetector->SetComponentSettings(LighterLight->SourceRadius, LighterLight->GetRelativeTransform());
}


void AAlex::CreateWidgets()
{
	CreatePauseWidget();

	CreateDotWidget();

	CreateFocusWidget();

	CreateInventoryWidget();
	
	CreateOpenInventoryWidget();
	
	CreateLighterReminderWidget();
	
	CreateConsumableWidget();
	
	MyController->OnNextInventoryItem.AddDynamic(InventoryWidget, &UInventory::ShowNextItem);
	MyController->OnPrevInventoryItem.AddDynamic(InventoryWidget, &UInventory::ShowPrevItem);

	MyController->OnKeyPressed.AddDynamic(OpenInventoryWidget,  &UOpenInventory::SetKeyMode);
	MyController->OnKeyPressed.AddDynamic(LighterReminderWidget,  &UOpenInventory::SetKeyMode);
	MyController->OnKeyPressed.AddDynamic(AltarWidget,  &UOpenInventory::SetKeyMode);
}

void AAlex::CreatePauseWidget()
{
	PauseWidget = CreateWidget<UPauseMenuWidget>(GetWorld(),PauseMenu);
	PauseWidget->AddToViewport(2);
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	PauseWidget->SetIsFocusable(true);
}

void AAlex::CreateDotWidget()
{
	DotWidget = CreateWidget<UCenterDotWidget>(GetWorld(),DotUI);
	DotWidget->AddToViewport(0);
	DotWidget->SetVisibility(ESlateVisibility::Visible);
}

void AAlex::CreateFocusWidget()
{
	AltarWidget = CreateWidget<UChangingdWidget>(GetWorld(),AltarUI);
	AltarWidget->AddToViewport(1);
	AltarWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AAlex::CreateInventoryWidget()
{
	InventoryWidget = CreateWidget<UInventory>(GetWorld(),InventoryMenu);
	InventoryWidget->AddToViewport(0);
	InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidget->SetIsFocusable(false);
}

void AAlex::CreateOpenInventoryWidget()
{
	OpenInventoryWidget = CreateWidget<UOpenInventory>(GetWorld(), OpenInventoryMenu);
	OpenInventoryWidget->AddToViewport(0);
	OpenInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	OpenInventoryWidget->SetIsFocusable(false);
}

void AAlex::CreateLighterReminderWidget()
{
	LighterReminderWidget = CreateWidget<UTutorialWidget>(GetWorld(), LighterRecordatoryMenu);
	LighterReminderWidget->AddToViewport(0);
	LighterReminderWidget->SetVisibility(ESlateVisibility::Hidden);
	LighterReminderWidget->SetIsFocusable(true);
}

void AAlex::CreateConsumableWidget()
{
	ConsumibleItemWidget = CreateWidget<UChangingdWidget>(GetWorld(), ConsumibleItemMenu);
	ConsumibleItemWidget->AddToViewport(0);
	ConsumibleItemWidget->SetVisibility(ESlateVisibility::Hidden);
	ConsumibleItemWidget->SetIsFocusable(true);
}

//---------------- Tick Methods
void AAlex::HeadBob()
{
	if(bFocus || bFocusing) return;
	
	if(bStun)
		MyController->ClientStartCameraShake(CameraShakeStun);
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

//---------------- Input Methods
void AAlex::MovePlayer(FVector2D vector)
{
	if(bFocusing || bFocus) return;
	
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
	if(bFocusing || bFocus) return;
	
	//if(bOnEvent)
	//{
	//	vector.X = FMath::Clamp(vector.X, this->VectorX.X, this->VectorX.Y);
	//	vector.Y = FMathf::Clamp(vector.Y, this->VectorY.X, this->VectorY.Y);
	//}

	AddControllerYawInput(vector.X * MyController->GetMouseSensitivity());
	AddControllerPitchInput(vector.Y * MyController->GetMouseSensitivity());
}

void AAlex::Interaction()
{
	if(!bCanTalk || !bCanInteract || bFocus || bFocusing) return;
	
	if(TalkSound != nullptr)
		MakeTalk();

	ActualInteractuable->Interaction();
	
	if(ActualInteractuable->IsPickable())
	{
		InventoryWidget->AddItemToInventory(ActualInteractuable->GetItemName(), ActualInteractuable->GetItemID());

		OpenInventoryWidget->SetVisibility(ESlateVisibility::Visible);
		
		if (!GetWorldTimerManager().IsTimerActive(TimerHandle_OpenInventoryWidget))
		{
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindLambda([&]
			{
				OpenInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			});
			
			//GetWorldTimerManager().SetTimer(TimerHandle_OpenInventoryWidget, TimerDelegate, 1.5f, false);
			GetWorldTimerManager().SetTimer(TimerHandle_OpenInventoryWidget, this, &AAlex::HideOpenInventoryWidget, 1.5f, false);
		}
	}
}

void AAlex::StartSprint()
{
	if(!bCanRun || bFocusing || bFocus) return;
	
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AAlex::StopSprint()
{
	if(!bCanRun || bFocusing || bFocus) return;
	
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AAlex::TurnLigherIfPossible()
{
	if(!bCanUseLigher || bFocusing || bFocus)
	{
		//if(!bCanSound) return;
		//	
		//UGameplayStatics::SpawnSound2D(this, LighterCDSound);
		//bCanSound = false;
		
		return;
	}
	
	CheckLighterOn();
}

void AAlex::DoorMovement(FVector2D vector)
{
	if(bFocusing || bFocus) return;
	
	DoorFloat = vector.X * MyController->GetMouseSensitivity();
}

void AAlex::OpenPause()
{
	if(bFocusing || bFocus) return;
	
	
	bPauseFlip = false;
	MyController->SetPauseGame(true);
	PauseWidget->SetVisibility(ESlateVisibility::Visible);
	PauseWidget->OnPauseOpen.Broadcast();
}

void AAlex::OpenInventory()
{
	if(!bPauseFlip || bFocusing || bFocus) return;
	
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

//---------------- Lighter Methods

void AAlex::MontageAnimOnOff()
{
	if(bFocusing || bFocus) return;
	
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

void AAlex::SetLighterAssetsVisibility(bool visibilityState)
{
	LighterLight->SetVisibility(visibilityState);
	Lighter->SetVisibility(visibilityState);
	FlamePlane->SetVisibility(visibilityState);
	WrittingsDetector->SetInteractionStatus(visibilityState);
}

void AAlex::ShowLighterReminder()
{
	LighterReminderWidget->SetVisibility(ESlateVisibility::Visible);

	if (!GetWorldTimerManager().IsTimerActive(TimerHandle_LighterReminder))
	{
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([&]
		{
			LighterReminderWidget->SetVisibility(ESlateVisibility::Hidden);
			TimerComponentForLighterDisplay->ActionFinished();
		});
		
		//GetWorldTimerManager().SetTimer(TimerHandle_LighterReminder, timerDelegate, 4.f, false);
		GetWorldTimerManager().SetTimer(TimerHandle_LighterReminder, this, &AAlex::HideLighterReminder, 4.f, false);
	}
}

void AAlex::HideLighterReminder()
{
	LighterReminderWidget->SetVisibility(ESlateVisibility::Hidden);
	TimerComponentForLighterDisplay->ActionFinished();
}

//---------------- Audio Methods
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

void AAlex::HideOpenInventoryWidget()
{
	OpenInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AAlex::HideConsumableWidget()
{
	ConsumibleItemWidget->SetVisibility(ESlateVisibility::Hidden);
}

//---------------- TimeLine
void AAlex::BindTimeLineMethods()
{
	//--- Targeting
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("CameraTargetTick"));
	TargetCameraTimeLine.AddInterpFloat(EmptyCurve, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("CameraTargetFinished"));
	TargetCameraTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);

	//--- Focusing
	FOnTimelineFloat CamFocusingTick;
	CamFocusingTick.BindUFunction(this, FName("CameraFocusTick"));
	FocusCameraTimeLine.AddInterpFloat(CurveFloat_FocusCamera, CamFocusingTick);
	
	FOnTimelineEventStatic CameraFocusingFinished;
	CameraFocusingFinished.BindUFunction(this, FName("CameraFocusFinished"));
	FocusCameraTimeLine.SetTimelineFinishedFunc(CameraFocusingFinished);
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

void AAlex::CameraFocusTick(float time)
{
	auto ewTransform = FMath::Lerp(GetMesh()->GetSocketLocation("head"), FocusCamTransform.GetLocation(), time);
	Camera->SetWorldLocation(ewTransform);

	if(bFocus)
	{
		auto ewRot = FMath::Lerp(LastCamTransform.GetRotation().Rotator(), FocusCamTransform.GetRotation().Rotator(), time);
		Camera->SetWorldRotation(ewRot);
	}
	else
	{
		auto ewRot = FMath::Lerp(Rot, FocusCamTransform.GetRotation().Rotator(), time);
		Camera->SetWorldRotation(ewRot);
	}
}

void AAlex::CameraFocusFinished()
{
	bFocusing = false;
	
	if(bFocus) return;
	
	MyController->SetControlRotation(Rot);
	Camera->bUsePawnControlRotation = true;
	MyController->OnCameraMoved.AddDynamic(this, &AAlex::MoveCamera);
}