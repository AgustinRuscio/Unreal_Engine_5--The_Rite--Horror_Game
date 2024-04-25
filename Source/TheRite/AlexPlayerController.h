//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/PlayerController.h"
#include "AlexPlayerController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerMovement, FVector2D, vectorInput);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartSprint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopSprint);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnLighterOn);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHoldingBTN, bool, IsHolding);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoveCamera, FVector2D, input);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenHint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseHint);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventory);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNextInventoryItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPrevInventoryItem);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCheckInputMode, bool,  isGamepad);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCheckKeyInputMode, bool,  isGamepad);


class UInputMappingContext;
class UInputAction;
class ALevelsGameState;
class UWidgetInteractionComponent;

UCLASS()
class THERITE_API AAlexPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Settings")
	float MouseSensitivity = 1.f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	ALevelsGameState* GameState;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingCOntext;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* MovePlayerAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* LighterAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* CameraLookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* OpenHintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* PuaseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* NextInventoryItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* PrevInventoryItemAction;

	
	void PlayerMovement(const FInputActionValue& value);
	
	void StartSprint(const FInputActionValue& value);
	void StopSprint(const FInputActionValue& value);

	void LighterOn(const FInputActionValue& value);
	
	void InteractionPressed(const FInputActionValue& value);
	void HoldingBTN(const FInputActionValue& value);

	void CameraMoved(const FInputActionValue& value);
	void DoorMoved(const FInputActionValue& value);

	void OpenHint(const FInputActionValue& value);
	void CloseHint(const FInputActionValue& value);
	
	void Paused(const FInputActionValue& value);
	void Inventory(const FInputActionValue& value);
	void NextInventoryItem(const FInputActionValue& value);

	
	bool bIsUsingGamepad;
	
	UFUNCTION(BlueprintCallable, Category="Gamepad")
	void SetIsGamepad(const bool bIsGamepad);
	
	UFUNCTION(BlueprintCallable, Category="Gamepad")
	bool GetIsGamepad() const;

	UFUNCTION()
	void RecieveLoadedData(float newSensitivity);

	ALevelsGameState* gs;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UWidgetInteractionComponent* WidgetInteractionComponent;

	void PrevInventoryItem(const FInputActionValue& value);
	virtual void BeginPlay() override;

	UFUNCTION()
	void LoadValues();
	void BindActions();
	void UnbindActions();
	void SetInventoryInputs();
	void SetDoorInputs();

public:
	AAlexPlayerController();
	~AAlexPlayerController();
	bool GetIsUsingGamepad() const;
	void SetPauseGame(bool PauseState);
	void SetDoorMode(bool newMode);
	void SetUIOnly(bool uiMode);
	void SetEventInput();
	void SetNormalInput();

	void DisableInput(APlayerController* PlayerController) override;

	void EnableInput(APlayerController* PlayerController) override;

	UFUNCTION(BlueprintCallable)
	float GetMouseSensitivity() const;

	UFUNCTION(BlueprintCallable)
	void SetMouseSensitivity(float newSensitivity);
	
	FPlayerMovement OnPlayerMovement;
	
	FStopSprint OnStopSprint;
	FStartSprint OnStartSprint;

	FTurnLighterOn OnLighter;

	FInteractionPressed OnInteractionPressed;
	FHoldingBTN OnHoldingBtn;

	FMoveCamera OnCameraMoved;
	FMoveCamera OnCameraMovedDoor;

	FOpenHint OnOpenHint;
	FCloseHint OnCloseHint;

	FPaused OnPause;
	FInventory OnInventory;
	
	FNextInventoryItem OnNextInventoryItem;
	FPrevInventoryItem OnPrevInventoryItem;

	FCheckInputMode OnKeyPressed;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCheckKeyInputMode OnAnyKeyPressed;
};