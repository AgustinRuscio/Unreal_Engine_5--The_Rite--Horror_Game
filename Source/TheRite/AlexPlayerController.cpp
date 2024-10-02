//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "AlexPlayerController.h"
#include "Components/WidgetInteractionComponent.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "Framework/Application/SlateApplication.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerStateTheRite.h"
#include "Kismet/GameplayStatics.h"

#define PRINT(x) UE_LOG(LogTemp, Warning, TEXT(x));

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AAlexPlayerController::AAlexPlayerController()
{
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionComp"));
	WidgetInteractionComponent->SetupAttachment(RootComponent);
}

//----------------------------------------------------------------------------------------------------------------------
AAlexPlayerController::~AAlexPlayerController()
{
	OnPlayerMovement.Clear();
	OnStopSprint.Clear();
	OnStartSprint.Clear();
	OnLighter.Clear();
	OnInteractionPressed.Clear();
	OnHoldingBtn.Clear();
	OnCameraMoved.Clear();
	OnCameraMovedDoor.Clear();
	OnPause.Clear();
	OnInventory.Clear();
	OnNextInventoryItem.Clear();
	OnPrevInventoryItem.Clear();
	OnKeyPressed.Clear();
	OnAnyKeyPressed.Clear();
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Getter Methods
bool AAlexPlayerController::GetIsUsingGamepad() const
{
	return bIsUsingGamepad;
}

//----------------------------------------------------------------------------------------------------------------------
float AAlexPlayerController::GetMouseSensitivity() const
{
	return MouseSensitivity;
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region Actions Methods
void AAlexPlayerController::EnableInput(APlayerController* PlayerController)
{
	Super::EnableInput(PlayerController);
	SetIgnoreLookInput(false);
	SetIgnoreMoveInput(false);
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::DisableInput(APlayerController* PlayerController)
{
	Super::DisableInput(PlayerController);
	SetIgnoreLookInput(true);
	SetIgnoreMoveInput(true);
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::SetNormalInput()
{
	BindActions();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::SetPauseGame(bool PauseState)
{
	SetPause(PauseState);
	bShowMouseCursor = PauseState;
	
	if (PauseState)
		SetInputMode(FInputModeGameAndUI().SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways));
	else
		SetInputMode(FInputModeGameOnly());
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::SetDoorMode(bool newMode)
{
	newMode ?
		SetDoorInputs() : BindActions();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::SetUIOnly(bool uiMode, bool showCursos)
{
	bShowMouseCursor = showCursos;
	
	uiMode ? SetInventoryInputs():
	BindActions();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::SetEventInput()
{
	UnbindActions();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingCOntext, 0);

	if(UEnhancedInputComponent* enhantedComponent =  CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		enhantedComponent->BindAction(CameraLookAction, ETriggerEvent::Triggered, this, &AAlexPlayerController::CameraMoved);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::SetFocusInput()
{
	UnbindActions();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingCOntext, 0);

	if(UEnhancedInputComponent* enhantedComponent =  CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		enhantedComponent->BindAction(PrevInventoryItemAction, ETriggerEvent::Started, this, &AAlexPlayerController::PrevInventoryItem);
		enhantedComponent->BindAction(NextInventoryItemAction, ETriggerEvent::Started, this, &AAlexPlayerController::NextInventoryItem);
		
		enhantedComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AAlexPlayerController::InteractionPressed);
		
		enhantedComponent->BindAction(BackAction, ETriggerEvent::Triggered, this, &AAlexPlayerController::BackFromFocus);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::SetNewCursorVisibilityState(bool IsActive)
{
	bShowMouseCursor = IsActive;
}
#pragma endregion 
//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::SetMouseSensitivity(float newSensitivity)
// borrar porque esta en UI vieja
{
	MouseSensitivity = newSensitivity;
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::PlayRumbleFeedBack(float intensity, float duration, bool LLarge, bool LSmall, bool RLarge,
	bool RSmall)
{
	PlayDynamicForceFeedback(intensity, duration, LLarge, LSmall, RLarge, RSmall,  EDynamicForceFeedbackAction::Start);
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
bool AAlexPlayerController::GetIsGamepad() const
{
	return bIsUsingGamepad;
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::BeginPlay()
{
	bEnableClickEvents = true; 
	bEnableMouseOverEvents = true;

	LoadValues();
	
	FSlateApplication::Get().OnApplicationActivationStateChanged()
	.AddUObject(this, &AAlexPlayerController::OnWindowFocusChanged);
		
	BindActions();
}
#pragma region Loading Methods

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::LoadValues()
{
	auto ps = Cast<APlayerStateTheRite>(PlayerState);
	MouseSensitivity = ps->GetMouseSensitivity();
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region Binding Methods
void AAlexPlayerController::BindActions()
{
	UnbindActions();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingCOntext, 0);
	
	if(UEnhancedInputComponent* enhantedComponent =  CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		enhantedComponent->BindAction(MovePlayerAction, ETriggerEvent::Triggered ,this, &AAlexPlayerController::PlayerMovement);
		
		enhantedComponent->BindAction(SprintAction, ETriggerEvent::Triggered ,this, &AAlexPlayerController::StartSprint);
		enhantedComponent->BindAction(SprintAction, ETriggerEvent::Completed ,this, &AAlexPlayerController::StopSprint);

		enhantedComponent->BindAction(LighterAction, ETriggerEvent::Started, this, &AAlexPlayerController::LighterOn);

		enhantedComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AAlexPlayerController::InteractionPressed);
		enhantedComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAlexPlayerController::HoldingBTN);
		enhantedComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &AAlexPlayerController::HoldingBTN);

		enhantedComponent->BindAction(CameraLookAction, ETriggerEvent::Triggered, this, &AAlexPlayerController::CameraMoved);
		
		enhantedComponent->BindAction(PuaseAction, ETriggerEvent::Started, this, &AAlexPlayerController::Paused);
		enhantedComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AAlexPlayerController::Inventory);
	}

	SetInputMode(FInputModeGameOnly());
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::UnbindActions()
{
	if(UEnhancedInputComponent* enhantedComponent =  CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		enhantedComponent->ClearActionBindings();
	}
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region Input Methods
void AAlexPlayerController::PlayerMovement(const FInputActionValue& value)
{
	FVector2D moveAxis = value.Get<FVector2D>();
	OnPlayerMovement.Broadcast(moveAxis);
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::StartSprint(const FInputActionValue& value)
{
	OnStartSprint.Broadcast();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::StopSprint(const FInputActionValue& value)
{
	OnStopSprint.Broadcast();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::LighterOn(const FInputActionValue& value)
{
	OnLighter.Broadcast();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::InteractionPressed(const FInputActionValue& value)
{
	OnInteractionPressed.Broadcast();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::HoldingBTN(const FInputActionValue& value)
{
	OnHoldingBtn.Broadcast(value.Get<bool>());
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::CameraMoved(const FInputActionValue& value)
{
	FVector2d moveAxis = value.Get<FVector2d>();
	OnCameraMoved.Broadcast(moveAxis);
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::DoorMoved(const FInputActionValue& value)
{
	FVector2d moveAxis = value.Get<FVector2d>();
	OnCameraMovedDoor.Broadcast(moveAxis);
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::Paused(const FInputActionValue& value)
{
	OnPause.Broadcast();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::Inventory(const FInputActionValue& value)
{
	OnInventory.Broadcast();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::NextInventoryItem(const FInputActionValue& value)
{
	OnNextInventoryItem.Broadcast();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::PrevInventoryItem(const FInputActionValue& value)
{
	OnPrevInventoryItem.Broadcast();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::BackFromFocus(const FInputActionValue& value)
{
	OnLeaveFocus.Broadcast();
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::SetInventoryInputs()
{
	UnbindActions();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingCOntext, 0);
	
	if(UEnhancedInputComponent* enhantedComponent =  CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		enhantedComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AAlexPlayerController::Inventory);

		enhantedComponent->BindAction(NextInventoryItemAction, ETriggerEvent::Started, this, &AAlexPlayerController::NextInventoryItem);
		enhantedComponent->BindAction(PrevInventoryItemAction, ETriggerEvent::Started, this, &AAlexPlayerController::PrevInventoryItem);
	}
	
	SetInputMode(FInputModeGameAndUI().SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways));
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::SetDoorInputs()
{
	UnbindActions();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingCOntext, 0);
	
	if(UEnhancedInputComponent* enhantedComponent =  CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		enhantedComponent->BindAction(CameraLookAction, ETriggerEvent::Triggered, this, &AAlexPlayerController::DoorMoved);
		
		enhantedComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAlexPlayerController::HoldingBTN);
		enhantedComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &AAlexPlayerController::HoldingBTN);
	}
}
#pragma endregion 

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::SetIsGamepad(const bool bIsGamepad)
{
	bIsUsingGamepad = bIsGamepad;
	OnKeyPressed.Broadcast(bIsGamepad);
}

//----------------------------------------------------------------------------------------------------------------------
void AAlexPlayerController::OnWindowFocusChanged(bool bIsFocused)
{
	if (bIsFocused)
	{
		GEngine->SetMaxFPS(75);
		OnPause.Broadcast();
	}
	else
	{
		GEngine->SetMaxFPS(10.0f);
	}
}