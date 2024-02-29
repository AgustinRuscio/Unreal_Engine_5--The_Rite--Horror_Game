#include "AlexPlayerController.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AAlexPlayerController::PlayerMovement(const FInputActionValue& value)
{
	FVector2D moveAxis = value.Get<FVector2D>();
	OnPlayerMovement.Broadcast(moveAxis);
}

void AAlexPlayerController::StartSprint(const FInputActionValue& value)
{
	OnStartSprint.Broadcast();
}

void AAlexPlayerController::StopSprint(const FInputActionValue& value)
{
	OnStopSprint.Broadcast();
}

void AAlexPlayerController::LighterOn(const FInputActionValue& value)
{
	OnLighter.Broadcast();
}

void AAlexPlayerController::InteractionPressed(const FInputActionValue& value)
{
	OnInteractionPressed.Broadcast();
}

void AAlexPlayerController::HoldingBTN(const FInputActionValue& value)
{
	OnHoldingBtn.Broadcast(value.Get<bool>());
}

void AAlexPlayerController::CameraMoved(const FInputActionValue& value)
{
	FVector2d moveAxis = value.Get<FVector2d>();
	OnCameraMoved.Broadcast(moveAxis);
}

void AAlexPlayerController::OpenHint(const FInputActionValue& value)
{
	OnOpenHint.Broadcast();
}

void AAlexPlayerController::CloseHint(const FInputActionValue& value)
{
	OnCloseHint.Broadcast();
}

void AAlexPlayerController::Paused(const FInputActionValue& value)
{
	OnPause.Broadcast();
}

void AAlexPlayerController::Inventory(const FInputActionValue& value)
{
	OnInventory.Broadcast();
}

void AAlexPlayerController::NextInventoryItem(const FInputActionValue& value)
{
	OnNextInventoryItem.Broadcast();
}

void AAlexPlayerController::PrevInventoryItem(const FInputActionValue& value)
{
	OnPrevInventoryItem.Broadcast();
}


void AAlexPlayerController::BeginPlay()
{
	bEnableClickEvents = true; 
	bEnableMouseOverEvents = true;

	BindActions();
}

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

		enhantedComponent->BindAction(OpenHintAction, ETriggerEvent::Triggered, this, &AAlexPlayerController::OpenHint);
		enhantedComponent->BindAction(OpenHintAction, ETriggerEvent::Completed, this, &AAlexPlayerController::CloseHint);
		enhantedComponent->BindAction(OpenHintAction, ETriggerEvent::Canceled, this, &AAlexPlayerController::CloseHint);
		
		enhantedComponent->BindAction(PuaseAction, ETriggerEvent::Started, this, &AAlexPlayerController::Paused);
		enhantedComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AAlexPlayerController::Inventory);
	}
}

void AAlexPlayerController::UnbindActions()
{
	if(UEnhancedInputComponent* enhantedComponent =  CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		enhantedComponent->ClearActionBindings();
	}
}

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
}

AAlexPlayerController::AAlexPlayerController()
{
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionComp"));
	WidgetInteractionComponent->SetupAttachment(RootComponent);
}


void AAlexPlayerController::SetPauseGame(bool PauseState)
{
	SetPause(PauseState);
	bShowMouseCursor = PauseState;
	
	if (PauseState)
		SetInputMode(FInputModeGameAndUI());
	else
		SetInputMode(FInputModeGameOnly());
}

void AAlexPlayerController::SetUIOnly(bool uiMode)
{
	UE_LOG(LogTemp, Warning, TEXT("INVENTORY %d"), uiMode)
	bShowMouseCursor = uiMode;
	
	uiMode ? 
	SetInventoryInputs(), SetInputMode(FInputModeGameAndUI()):
	BindActions(), SetInputMode(FInputModeGameOnly());
	
}
void AAlexPlayerController::DisableInput(APlayerController* PlayerController)
{
	Super::DisableInput(PlayerController);
	SetIgnoreLookInput(true);
	SetIgnoreMoveInput(true);
}

void AAlexPlayerController::EnableInput(APlayerController* PlayerController)
{
	Super::EnableInput(PlayerController);
	SetIgnoreLookInput(false);
	SetIgnoreMoveInput(false);
}