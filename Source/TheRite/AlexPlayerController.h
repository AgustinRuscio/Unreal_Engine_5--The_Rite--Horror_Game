#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerInput.h"
#include "Components/WidgetInteractionComponent.h"
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

UCLASS()
class THERITE_API AAlexPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingCOntext;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* MovePlayerAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* LighterAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* CameraLookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* OpenHintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* PuaseAction;

	
	void PlayerMovement(const FInputActionValue& value);
	
	void StartSprint(const FInputActionValue& value);
	void StopSprint(const FInputActionValue& value);

	void LighterOn(const FInputActionValue& value);
	
	void InteractionPressed(const FInputActionValue& value);
	void HoldingBTN(const FInputActionValue& value);

	void CameraMoved(const FInputActionValue& value);

	void OpenHint(const FInputActionValue& value);
	void CloseHint(const FInputActionValue& value);
	
	void Paused(const FInputActionValue& value);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UWidgetInteractionComponent* WidgetInteractionComponent;

	virtual void BeginPlay() override;

public:
	AAlexPlayerController();
	void SetPauseGame(bool PauseState);

	void DisableInput(APlayerController* PlayerController) override;

	void EnableInput(APlayerController* PlayerController) override;
	FPlayerMovement OnPlayerMovement;
	
	FStopSprint OnStopSprint;
	FStartSprint OnStartSprint;

	FTurnLighterOn OnLighter;

	FInteractionPressed OnInteractionPressed;
	FHoldingBTN OnHoldingBtn;

	FMoveCamera OnCameraMoved;

	FOpenHint OnOpenHint;
	FCloseHint OnCloseHint;

	FPaused OnPause;
};