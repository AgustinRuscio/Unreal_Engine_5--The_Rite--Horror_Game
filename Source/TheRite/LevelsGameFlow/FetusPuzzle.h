//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FetusPuzzle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFetuPuzzleComplete);

class ATargetPoint;
class AFetus;
class ADoor;
class ALightsTheRite;
class AInteractor;
class AAlex;

UCLASS()
class THERITE_API AFetusPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	AFetusPuzzle();

	bool IsActive() const;
	
//---------------- System Class Methods
	virtual void BeginPlay() override;

private:
	void LightsOut();
	void LightsOn();

	UFUNCTION()
	void OnInteraction(AInteractor* interactor);
	
	UFUNCTION()
	void ResetPuzzle();
	
	UFUNCTION()
	void CheckNextPuzzleStep();
	
	UFUNCTION()
	void NextStep();
	
	UFUNCTION()
	void PuzzleComplete();

	void ReLocateFetus();

	void RemoveFirstRightFetus();

public:	
	FOnFetuPuzzleComplete OnPuzzleComplete;
	
private:
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	bool bActive;
	
	bool bPuzzleActivated;
	bool bFirstInteraction = true;
	
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	int MaxFetusPerRound;
	
	int TotalPuzzleStps = 0;
	
	float OffsetLightsOn;
	//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Audio", meta=(AllowPrivateAccess = true))
	USoundBase* SFX_CorrectInteraction;
	
	UPROPERTY(EditAnywhere, Category = "Audio", meta=(AllowPrivateAccess = true))
	USoundBase* SFX_WrongInteraction;
	
	//-------- Lights
	UPROPERTY(EditAnywhere, Category = "Lights", meta=(AllowPrivateAccess = true))
	TArray<ALightsTheRite*> RoomLights;
	
	//-------- Taregt Points
	UPROPERTY(EditAnywhere, Category = "Position", meta=(AllowPrivateAccess = true))
	TArray<ATargetPoint*> PosiblePosition;
	
	TArray<ATargetPoint*> AUXPosiblePosition;
	
	//-------- TimeLine
	FTimerHandle Timer_LightsOn;

//---------------------------------------- In game Objects
	UPROPERTY(EditAnywhere, Category = "Fetus", meta=(AllowPrivateAccess = true))
	TArray<AFetus*> AllFetus;

	TArray<AFetus*> RegularFetus;

	TArray<AFetus*> RightFetus;

	TArray<AFetus*> AUXRightFetus;
	
	UPROPERTY(EditAnywhere, Category = "Door", meta=(AllowPrivateAccess = true))
	ADoor* RoomDoor;

	AAlex* Player;
};