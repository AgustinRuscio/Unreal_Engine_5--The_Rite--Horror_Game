//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "SaveData.h"
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFocusBack);

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

public:
	AAlexPlayerController();
	~AAlexPlayerController();

//---------------- Getter Methods
	bool GetIsUsingGamepad() const;
	
	UFUNCTION(BlueprintCallable)
	float GetMouseSensitivity() const;
	
//---------------- Actions Methods
	void EnableInput(APlayerController* PlayerController) override;
	void DisableInput(APlayerController* PlayerController) override;
	
	void SetNormalInput();
	void SetPauseGame(bool PauseState);
	void SetDoorMode(bool newMode);
	void SetUIOnly(bool uiMode, bool ShowCursor);
	void SetEventInput();
	void SetFocusInput();
	void SetNewCursorVisibilityState(bool IsActive);
	
	UFUNCTION(BlueprintCallable) // borrar porque esta en UI vieja
	void SetMouseSensitivity(float newSensitivity);
	
	void PlayRumbleFeedBack(float intensity, float duration, bool LLarge, bool LSmall, bool  RLarge, bool RSmall);
	
private:
	UFUNCTION(BlueprintCallable, Category="Gamepad")
	bool GetIsGamepad() const;
	
	virtual void BeginPlay() override;
	
	//---------------- Loading Methods
	void LoadValues();
	
//---------------- Binding Methods
	void BindActions();
	void UnbindActions();
	
//---------------- Input Methods
	void PlayerMovement(const FInputActionValue& value);
	
	void StartSprint(const FInputActionValue& value);
	void StopSprint(const FInputActionValue& value);

	void LighterOn(const FInputActionValue& value);
	
	void InteractionPressed(const FInputActionValue& value);
	void HoldingBTN(const FInputActionValue& value);

	void CameraMoved(const FInputActionValue& value);
	void DoorMoved(const FInputActionValue& value);

	void Paused(const FInputActionValue& value);
	void Inventory(const FInputActionValue& value);
	void NextInventoryItem(const FInputActionValue& value);
	void PrevInventoryItem(const FInputActionValue& value);
	void BackFromFocus(const FInputActionValue& value);
	
	void SetInventoryInputs();
	void SetDoorInputs();

	UFUNCTION(BlueprintCallable, Category="Gamepad")
	void SetIsGamepad(const bool bIsGamepad);

	void OnWindowFocusChanged(bool bIsFocused);
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UWidgetInteractionComponent* WidgetInteractionComponent;
	
	FPlayerMovement OnPlayerMovement;
	
	FStopSprint OnStopSprint;
	FStartSprint OnStartSprint;

	FTurnLighterOn OnLighter;

	FInteractionPressed OnInteractionPressed;
	FHoldingBTN OnHoldingBtn;

	FMoveCamera OnCameraMoved;
	FMoveCamera OnCameraMovedDoor;

	FPaused OnPause;
	FInventory OnInventory;
	FOnFocusBack OnLeaveFocus;
	
	FNextInventoryItem OnNextInventoryItem;
	FPrevInventoryItem OnPrevInventoryItem;

	FCheckInputMode OnKeyPressed;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCheckKeyInputMode OnAnyKeyPressed;
	
private:
	bool bIsUsingGamepad;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	float MouseSensitivity = 1.f;
	
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
	UInputAction* BackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* PuaseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* NextInventoryItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* PrevInventoryItemAction;
};