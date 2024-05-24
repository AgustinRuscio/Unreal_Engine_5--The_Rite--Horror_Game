//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "TheRite/EnumsContainer.h"
#include "TheRite/Interactuables/Altar.h"
#include "GameFramework/Character.h"
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

public:
	AAlex();
	
//---------------- Getter Methods
	bool IsHoldInteractBTN() const;
	bool CheckCanDrag() const;
	bool GetFocusingState() const;
	
	float GetDoorFloat() const;
	float GetInteractionRange() const;
	
	UCameraComponent* GetCamera() const;
	
//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

//---------------- Action Methods
	UFUNCTION()
	void CameraTargeting(FVector Target);
	
	void ForceTalk(USoundBase* Voice);
	
	void CallPauseFunc();
	
	UFUNCTION()
	void ForceEnableInput();
	void ForceDisableInput();
	
	void ForceTurnLighterOn();
	void ForceLighterOff();
	
	void OnJumpScare();
	
	void RemoveFromInventory(FString itemName, PickableItemsID id);
	
//---------------- Setter Methods
	void SetPlayerOptions(bool canRun, bool canUseLighter, bool showLighterReminder);
	void SetCanUseLighterState(bool lighterState);
	
	void SetDraggingState(bool shouldCheck, ADoor* Door);
	void SetCameraStun(bool stun);
	
	void SetEventMode(bool onOff, float minX, float maxX, float minY, float maxY);
	
//---------------- View Methods
	void BackToNormalView(FTransform FromTransform, FVector ExitingVector, FRotator ExitingRotation);
	void OnFocusMode(FTransform NewTransform, FRotator ExitingRotation);
	void MoveCamera(FVector NewCameraPos);
	void MakeCameraView(FRotator Rot);
	
private:
//---------------- Checker Methods
	bool IsDoorCheck(IIInteractuable* checked);
	
	UFUNCTION()
	void CheckHolding(bool HoldingState);
	
	void InteractableCheck();
	
	void CheckLighterCooldDown(float deltaTime);
	
//---------------- Initialization Methods
	void CreateWritingDetector();
	
	void CreateWidgets();

	void CreatePauseWidget();
	void CreateDotWidget();
	void CreateFocusWidget();
	void CreateInventoryWidget();
	void CreateOpenInventoryWidget();
	void CreateLighterReminderWidget();
	void CreateConsumableWidget();
	
//---------------- Tick Methods
	void HeadBob();
	
	void CheckLighterOn();
	
//---------------- Input Methods
	UFUNCTION()
	void MovePlayer(FVector2D vector);
	
	UFUNCTION()
	void MoveCamera(FVector2D vector);

	UFUNCTION()
	void Interaction();
	
	UFUNCTION()
	void StartSprint();
	
	UFUNCTION()
	void StopSprint();
	
	UFUNCTION()
	void TurnLigherIfPossible();
	
	UFUNCTION()
	void DoorMovement(FVector2D vector);
	
	UFUNCTION()
	void OpenPause();
	UFUNCTION()
	void OpenInventory();
	
//---------------- Lighter Methods
	UFUNCTION()
	void MontageAnimOnOff();
	
	void LighterSoundTimer(float deltaTime);
	
	void SetLighterAssetsVisibility(bool visibilityState);

	UFUNCTION()
	void ShowLighterReminder();
	void HideLighterReminder();

//---------------- Audio Methods
	void MakeTalk();
	
	UFUNCTION()
	void OnAudioFinished();
	
	void StopTalking();
	
//---------------- TimeLine
	void BindTimeLineMethods();
	
	UFUNCTION()
	void CameraTargetTick(float time);
	
	UFUNCTION()
	void CameraTargetFinished();

	UFUNCTION()
	void CameraFocusTick(float time);
	
	UFUNCTION()
	void CameraFocusFinished();
	
public:
	UPROPERTY(BlueprintReadOnly)
	bool bLighter;
	
	FAllItemsCollected OnAllItemCollected;
	FLighterMontage OnLighterAnimMontage;
	FJumpscaredFinished OnJumpscaredFinished;
	
private:
	//UPROPERTY(EditAnywhere, Category = "Lighter values")
	bool bCanUseLigher;
	bool bShowLighterReminder;
	bool bCanRun = true;
	bool bCanTalk = true;
	bool bCanSound = true;
	bool bCanInteract = false;
	bool bFocusing = false;
	
	bool bFocus = false;
	bool bStun = false;
	bool bOnEvent = false;
	bool bLighterOnCD = false;
	bool bDoorWasLocked = false;

	bool bInventoryFlip = true;
	bool bPauseFlip = true;

	bool bHoldingInteractBTN = false;
	bool bIsDragging = false;
	
	UPROPERTY(EditAnywhere, Category = "General")
	float WalkSpeed = 400.0f;
	
	UPROPERTY(EditAnywhere, Category = "General")
	float RunSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category = "General")
	float Sensitivity;
	
	UPROPERTY(EditAnywhere, Category = "General")
	float RangeInteractuable;
	
	UPROPERTY(EditAnywhere, Category = "General")
	float MaxLighterTime = 12.0f;
	
	UPROPERTY(EditAnywhere, Category = "General")
	float LighterCD = 5.0f;
	
	float LighterTimer = 0;
	float AudioTimer;
	float DoorFloat;

	FVector2D VectorX;
	FVector2D VectorY;

	FVector CameraLookTarget;
	FRotator Rot;
	
	FTransform LastCamTransform;
	FTransform FocusCamTransform;

	//-------- Meshes Collider
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* FlamePlane;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UChildActorComponent* Lighter;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	USkeletalMeshComponent* ScreamerSkeleton;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UAnimationAsset* ScreamerAnim;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UAnimMontage* HintAnimMontage;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UAnimMontage* LighterMontage;

	//-------- Camera
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> CameraShakeWalk;
	
	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> CameraShakeRun;
	
	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> CameraShakeIdle;
	
	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> CameraShakeStun;
	
	//-------- Audio
	UAudioComponent* TempAudio = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* LighterCDSound;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* LighterOn;
	
	USoundBase* TalkSound;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* BreathSound;
	
	//-------- TimeLine
	FTimerHandle ScreamerTimerHanlde;
	FTimerHandle OpeninventorywidgetTimerHandle;
	FTimerHandle LighterReminderTimer;
	FTimerHandle ConsumibleWidgetTimer;
	FTimerHandle aa;

	FTimeline TargetCameraTimeLine;
	FTimeline FocusCameraTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "TimeLine")
	UCurveFloat* EmptyCurve;
	
	UPROPERTY(EditAnywhere, Category = "TimeLine")
	UCurveFloat* CurveFloat_FocusCamera;

	//-------- Lights
	UPROPERTY(EditAnywhere, Category = "Lights")
	UPointLightComponent* LighterLight;
	
	UPROPERTY(EditAnywhere, Category = "Lights")
	UPointLightComponent* BodyLight;

	//-------- Widgets
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPauseMenuWidget> PauseMenu;
	UPauseMenuWidget* PauseWidget;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UTutorialWidget> LighterRecordatoryMenu;
	UTutorialWidget* LighterReminderWidget;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UOpenInventory> OpenInventoryMenu;
	UOpenInventory* OpenInventoryWidget;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UInventory> InventoryMenu;
	UInventory* InventoryWidget;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UChangingdWidget> ConsumibleItemMenu;
	UChangingdWidget* ConsumibleItemWidget;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UCenterDotWidget> DotUI;
	UCenterDotWidget* DotWidget;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UChangingdWidget> AltarUI;
	UChangingdWidget* AltarWidget;

	
	//-------- Components
	UPROPERTY(EditAnywhere, Category="Components")
	UTimerActionComponent* TimerComponentForLighterDisplay;

	//-------- Interaction
	IIInteractuable* ActualInteractuable;
	FString RemovableName;
	PickableItemsID RemovableID;
	UPROPERTY(EditAnywhere, Category = "Ligher")
	TSubclassOf<AWrittingsDetector> DetectorSubclass;
	AWrittingsDetector* WrittingsDetector;
	

	
	//-------- Materials
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	UMaterialInstance* NormalMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	UMaterialInstance* AggresiveMaterial;
	
	
	AAlexPlayerController* MyController;
	ADoor* DoorChecked;
};