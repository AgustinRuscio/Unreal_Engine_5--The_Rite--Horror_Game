#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HideAndSeekPuzzle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideSeekComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideSeekStarted);

class ALightsTheRite;
class AAlex;
class AInteractor;
class ATargetPoint;


UCLASS()
class THERITE_API AHideAndSeekPuzzle : public AActor
{
	GENERATED_BODY()
	
public:
bool IsActive() const;
	
	AHideAndSeekPuzzle();
	virtual void BeginPlay() override;

private:
	void InitializeValues();
	
	UFUNCTION()
	void OnNextPuzzleStep(AInteractor* Interactable);
	
	void ReLocateInteractable();
	void LightsOff();
	void LightsOn();

	void PlayerLighterStateSetter(bool UseOfLighter);
	void InteractionFeedBack();
	
	void PuzzleCompleted();
	
public:
	FOnHideSeekComplete OnPuzzleStarted;
	FOnHideSeekComplete OnPuzzleComplete;

private:
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	bool bActive;
	
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	bool bIsFetus;
	
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	bool bLightsOnAfterCompleted;
	
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	bool bDestroyInteractableAfterCompleted;

	bool bFirstInteractionDone;
	
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	int8 RelocationsQuantity;
	
	int8 LocationIndex;

	UPROPERTY(EditAnywhere, Category = "Sound FX", meta=(AllowPrivateAccess = true))
	USoundBase* SFX_InteractionFX;

	UPROPERTY(EditAnywhere, Category = "Sound FX", meta=(AllowPrivateAccess = true))
	TArray<USoundBase*> SFX_AlexTalk;
	
	UPROPERTY(EditAnywhere, Category = "Target Points", meta=(AllowPrivateAccess = true))
	ATargetPoint* TargetPoints_InitialLocations;
	
	UPROPERTY(EditAnywhere, Category = "Target Points", meta=(AllowPrivateAccess = true))
	TArray<ATargetPoint*> TargetPoints_MainLocations;
	
	UPROPERTY(EditAnywhere, Category = "Target Points", meta=(AllowPrivateAccess = true))
	TArray<ATargetPoint*>  TargetPoints_SecondaryLocations;

	UPROPERTY(EditAnywhere, Category = "Interactable", meta=(AllowPrivateAccess = true))
	AInteractor*  Interactables_MainInteractable;

	UPROPERTY(EditAnywhere, Category = "Lights", meta=(AllowPrivateAccess = true))
	TArray<ALightsTheRite*> Lights_NeededLights;

	UPROPERTY(EditAnywhere, Category = "FeedBack", meta=(AllowPrivateAccess = true))
	TSubclassOf<UCameraShakeBase> CameraShake;
	
	AAlex* Player;
};