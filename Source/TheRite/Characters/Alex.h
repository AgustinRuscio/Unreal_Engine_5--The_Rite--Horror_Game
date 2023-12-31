#pragma once

#include "CoreMinimal.h"
#include "TheRite/Interactuables/Door.h"
#include "Components/TimelineComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/Widget.h"
#include "GameFramework/Character.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Interactuables/IInteractuable.h"
#include "TheRite/Widgets/CenterDotWidget.h"
#include "TheRite/Widgets/PauseMenuWidget.h"
#include "Alex.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAllItemsCollected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLighterMontage);

class UInputMappingContext;
class UInputAction;

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
	
	UPROPERTY(EditAnywhere, Category = "Hint")
	UChildActorComponent* Hint;
	
	UPROPERTY(EditAnywhere, Category = "Ligher")
	UChildActorComponent* Lighter;

	
	
	UPROPERTY(EditAnywhere, Category = "Ligher")
	UStaticMeshComponent* FlamePlane;
	
	UPROPERTY(EditAnywhere, Category = "Ligher")
	UPointLightComponent* LighterLight;

	
	UPROPERTY(EditAnywhere, Category = "Movement Value")
	float WalkSpeed = 400.0f;
	
	UPROPERTY(EditAnywhere, Category = "Movement Values")
	float RunSpeed = 600.0f;

	
	bool bCanInteract;

	IIInteractuable* ActualInteractuable;

	
	bool bLighterOnCD;


	UPROPERTY(EditAnywhere, Category = "Lighter values")
	float MaxLighterTime = 12.0f;
	float LighterTimer = 12.0f;
	
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	float LighterCD = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Lighter values")
	UMaterialInstance* NormalMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	UMaterialInstance* AggresiveMaterial;
	
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPauseMenuWidget> PauseMenu;
	
	UPauseMenuWidget* PuaseWidget;
	
	float BreathTimer;
	float AudioTimer;
	bool bCanSound = true;

	UPROPERTY(EditAnywhere, Category = "Lighter values")
	USoundBase* LighterCDSound;
	
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	USoundBase* LighterOn;

	UWidget* Hints;
	bool bHasHint;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UCenterDotWidget> DotUI;
	
	UCenterDotWidget* DotWidget;
	
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	float RangeInteractuable;

	UPROPERTY(EditAnywhere, Category = "Lighter values")
	bool bCanUseLigher;

	USoundBase* TalkSound;
	
	UPROPERTY(EditAnywhere, Category = "Lighter values")
	USoundBase* BreathSound;

	bool bCanTalk = true;

	float DoorFloat;

	bool bHoldingInteractBTN;

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

	UPROPERTY(EditAnywhere, Category = "Screamer")
	UAnimationAsset* ScreamerAnim;

	FTimerHandle ScreamerTimerHanlde;

	FTimeline TargetCameraTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCurveFloat* EmptyCurve;

	UFUNCTION()
	void CameraTargetTick(float time);
	UFUNCTION()
	void CameraTargetFinished();

	void BindTimeLineMethods();
	
	void BindActions();

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
	void Interaction();
	UFUNCTION()
	void CheckHolding(bool HoldingState);

	UFUNCTION()
	void OpenHint();
	UFUNCTION()
	void CloseHint();

	UFUNCTION()
	void OpenPause();

	UFUNCTION()
	
	void MontageAnimOnOff();
	
	void LighterSoundTimer(float deltaTime);
	void CheckLighterCooldDown(float deltaTime);

	void HeadBob();

	void Breath(float deltaTime);

	void InteractuableCheck();

	bool IsDoorCheck(IIInteractuable* checked);
	ADoor* DoorChecked;
	bool bDoorWasLocked;


	UAudioComponent* TempAudio = nullptr;
	void OnJumpScare();
	void TimeOver();

	void MakeTalk();
	
	UFUNCTION()
	void OnAudioFinished();

	void StopTalking();

	void CreateWidgets();
	
	FVector CameraLookTarget;
	
protected:
	virtual void BeginPlay() override;

public:	
	AAlex();

	
	UPROPERTY(BlueprintReadOnly)
	bool bLighter;
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CallPauseFunc();
	
	UFUNCTION()
	void CameraTargeting(FVector Target);
	
	void ForceTalk(USoundBase* Voice);
	
	bool IsHoldInteracBTN() const;

	float GetDoorFloat() const;
	UCameraComponent* GetCamera() const;
	
	FAllItemsCollected OnAllItemCollected;
	FLighterMontage OnLighterAnimMontage;
};