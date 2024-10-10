//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

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
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AHideAndSeekPuzzle();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	FOnHideSeekComplete OnPuzzleStarted;
	FOnHideSeekComplete OnPuzzleComplete;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	bool IsActive() const;

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	bool bActive;

	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	bool bIsFetus;

	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	bool bLightsOnAfterCompleted;

	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	bool bDestroyInteractableAfterCompleted;

	bool bFirstInteractionDone;

	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = "true"))
	int8 RelocationsQuantity;

	int8 LocationIndex;

	FName PostProcessModiferValue = "SpectralProximity";

	//---------- SFX
	UPROPERTY(EditAnywhere, Category = "Sound FX", meta=(AllowPrivateAccess = "true"))
	USoundBase* SFX_InteractionFX;

	UPROPERTY(EditAnywhere, Category = "Sound FX", meta=(AllowPrivateAccess = "true"))
	USoundBase* SFX_ClockTicking;

	UPROPERTY(EditAnywhere, Category = "Sound FX", meta=(AllowPrivateAccess = "true"))
	USoundBase* SFX_EventBegin;

	UPROPERTY(EditAnywhere, Category = "Sound FX", meta=(AllowPrivateAccess = "true"))
	TArray<USoundBase*> SFX_AlexTalk;


	//---------- TargetPoints
	UPROPERTY(EditAnywhere, Category = "Target Points", meta=(AllowPrivateAccess = "true"))
	ATargetPoint* TargetPoints_InitialLocations;
	
	UPROPERTY(EditAnywhere, Category = "Target Points", meta=(AllowPrivateAccess = "true"))
	TArray<ATargetPoint*> TargetPoints_MainLocations;
	
	UPROPERTY(EditAnywhere, Category = "Target Points", meta=(AllowPrivateAccess = "true"))
	TArray<ATargetPoint*>  TargetPoints_SecondaryLocations;


	//---------- Feed Back
	UPROPERTY(EditAnywhere, Category = "Lights", meta=(AllowPrivateAccess = "true"))
	TArray<ALightsTheRite*> Lights_NeededLights;

	UPROPERTY(EditAnywhere, Category = "FeedBack", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditAnywhere, Category= "FeedBack")
	class AProsProcessModifier* PostProcesModifierClass;

	//-------
	UPROPERTY(EditAnywhere, Category = "Interactable", meta=(AllowPrivateAccess = "true"))
	AInteractor*  Interactables_MainInteractable;

	AAlex* Player;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	
//---------------- Setter Methods
	void InitializeValues();
	void PlayerLighterStateSetter(bool UseOfLighter);
	
//---------------- Puzzle Methods
	UFUNCTION()
	void OnNextPuzzleStep(AInteractor* Interactable);
	void ReLocateInteractable();
	void PuzzleCompleted();
	
//---------------- Feed Back Methods
	void LightsOff();
	void LightsOn();
	void InteractionFeedBack();
};