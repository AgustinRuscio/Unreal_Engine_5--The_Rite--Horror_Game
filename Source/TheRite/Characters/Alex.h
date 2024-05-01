//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "TheRite/EnumsContainer.h"
#include "GameFramework/Character.h"
#include "TheRite/Interactuables/Altar.h"
#include "Alex.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAllItemsCollected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLighterMontage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FJumpscaredFinished);

class UInputMappingContext;
class UInputAction;
class UPointLightComponent;
class UCameraComponent;
class AWrittingsDetector;
class UTimerActionComponent;
class UPauseMenuWidget;
class UTutorialWidget;
class UOpenInventory;
class UInventory;
class UChangingdWidget;
class UCenterDotWidget;
class IIInteractuable;
class AAlexPlayerController;
class ADoor;

UCLASS()
class THERITE_API AAlex : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Character")
	UPointLightComponent* BodyLight;

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, Category = "Screamer")
	USkeletalMeshComponent* ScreamerSkeleton;
	
	UPROPERTY(EditAnywhere, Category = "Ligher")
	UChildActorComponent* Lighter;

	AWrittingsDetector* WrittingsDetector;

	UPROPERTY(EditAnywhere, Category = "Ligher")
	TSubclassOf<AWrittingsDetector> DetectorSubclass;
	
	UPROPERTY(EditAnywhere, Category = "Ligher")
	UStaticMeshComponent* FlamePlane;
	
	UPROPERTY(EditAnywhere, Category = "Ligher")
	UPointLightComponent* LighterLight;

	
	UPROPERTY(EditAnywhere, Category = "Movement Value")
	float WalkSpeed = 400.0f;
	
	UPROPERTY(EditAnywhere, Category = "Movement Values")
	float RunSpeed = 600.0f;

	
	bool bCanInteract;
	bool bFocus;

	IIInteractuable* ActualInteractuable;
	FString RemovableName;
	PickableItemsID RemovableID;
	
	bool bLighterOnCD = false;


	UPROPERTY(EditAnywhere, Category = "Lighter values")
	float MaxLighterTime = 12.0f;
	
	float LighterTimer = 0;
	
	UPROPERTY(EditAnywhere, Category="Components")
	UTimerActionComponent* TimerComponentForLighterDisplay;
	
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	float LighterCD = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Lighter values")
	UMaterialInstance* NormalMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	UMaterialInstance* AggresiveMaterial;
	
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPauseMenuWidget> PauseMenu;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UTutorialWidget> LighterRecordatoryMenu;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UOpenInventory> OpenInventoryMenu;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UInventory> InventoryMenu;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UChangingdWidget> ConsumibleItemMenu;
	
	UPauseMenuWidget* PauseWidget;
	UInventory* InventoryWidget;
	UOpenInventory* OpenInventoryWidget;
	UTutorialWidget* LighterReminderWidget;
	UChangingdWidget* ConsumibleItemWidget;
	
	float BreathTimer;
	float AudioTimer;
	bool bCanSound = true;
	bool bStun = false;

	bool bOnEvent= false;
	FVector2D VectorX;
	FVector2D VectorY;
	
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	USoundBase* LighterCDSound;
	
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	USoundBase* LighterOn;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UCenterDotWidget> DotUI;
	
	UCenterDotWidget* DotWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UChangingdWidget> AltarUI;
	
	UChangingdWidget* AltarWidget;
	
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	float RangeInteractuable;
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	float Sensitivity;

	UPROPERTY(EditAnywhere, Category = "Lighter values")
	bool bCanUseLigher;

	USoundBase* TalkSound;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* BreathSound;

	bool bCanTalk = true;
	bool bCanRun = true;

	float DoorFloat;

	bool bHoldingInteractBTN;
	bool bIsDragging;

	UPROPERTY(EditAnywhere, Category = "Hints")
	UAnimMontage* HintAnimMontage;
	
	UPROPERTY(EditAnywhere, Category = "Hints")
	UAnimMontage* LighterMontage;

	bool bPauseFlip = true;

	AAlexPlayerController* MyController;

	
	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> CameraShakeWalk;
	
	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> CameraShakeRun;
	
	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> CameraShakeIdle;
	
	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> CameraShakeStun;

	UPROPERTY(EditAnywhere, Category = "Screamer")
	UAnimationAsset* ScreamerAnim;

	FTimerHandle ScreamerTimerHanlde;
	
	FTimerHandle OpeninventorywidgetTimerHandle;

	FTimeline TargetCameraTimeLine;
	
	FTimerHandle LighterReminderTimer;
	FTimerHandle ConsumibleWidgetTimer;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCurveFloat* EmptyCurve;
	bool bInventoryFlip = true;

	UFUNCTION()
	void CameraTargetTick(float time);
	UFUNCTION()
	void CameraTargetFinished();

	void BindTimeLineMethods();
	
	UFUNCTION()
	void StartSprint();
	
	UFUNCTION()
	void StopSprint();
	
	UFUNCTION()
	void TurnLigherIfPossible();
	void CheckLighterOn();

	UFUNCTION()
	void MovePlayer(FVector2D vector);

	UFUNCTION()
	void MoveCamera(FVector2D vector);
	UFUNCTION()
	void DoorMovement(FVector2D vector);

	UFUNCTION()
	void Interaction();
	void CloseOpenInventoryWidget();
	UFUNCTION()
	void CheckHolding(bool HoldingState);
	
	UFUNCTION()
	void OpenPause();
	UFUNCTION()
	void OpenInventory();

	UFUNCTION()
	void MontageAnimOnOff();
	
	void LighterSoundTimer(float deltaTime);
	void CheckLighterCooldDown(float deltaTime);

	UFUNCTION()
	void ShowLighterReminder();
	void HideLighterReminder();


	void HeadBob();

	void InteractuableCheck();

	bool IsDoorCheck(IIInteractuable* checked);
	ADoor* DoorChecked;
	bool bDoorWasLocked;


	UAudioComponent* TempAudio = nullptr;
	void TimeOver();

	void MakeTalk();
	
	UFUNCTION()
	void OnAudioFinished();

	void StopTalking();

	void CreateWidgets();

	void SetLighterAssetsVisibility(bool visibilityState);

	void CheckTimeWhileLighterOff(float deltaTime);
	
	FVector CameraLookTarget;
	FVector LastCameraPos;
	FRotator LastCameraRot;

	
	
protected:
	virtual void BeginPlay() override;

public:	
	AAlex();

	
	void SetPlayerOptions(bool canRun, bool canUseLighter);

	UPROPERTY(BlueprintReadOnly)
	bool bLighter;
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CallPauseFunc();

	void SetDraggingState(bool shouldCheck, ADoor* Door);

	void SetCameraStun(bool stun);
	
	UFUNCTION()
	void CameraTargeting(FVector Target);
	
	void ForceTalk(USoundBase* Voice);
	
	bool IsHoldInteracBTN() const;

	bool CheckCanDrag() const;
	float GetDoorFloat() const;
	
	void SetCanUseLigherState(bool lighterState);
	void ForceTurnLighterOn();

	void OnJumpScare();

	void ForceDisableInput();
	UFUNCTION()
	void ForceEnableInput();
	void ForceLighterOff();
	
	void SetEventMode(bool onOff, float minX, float maxX, float minY, float maxY);
	void RemoveFromInventory(FString itemName, PickableItemsID id);


	
	void BackToNormalView();
	void OnFocusMode(FVector NewCameraPos, FRotator NewCameraRor);
	void MoveCamera(FVector NewCameraPos);
	
	UCameraComponent* GetCamera() const;
	
	FAllItemsCollected OnAllItemCollected;
	FLighterMontage OnLighterAnimMontage;
	FJumpscaredFinished OnJumpscaredFinished;
};