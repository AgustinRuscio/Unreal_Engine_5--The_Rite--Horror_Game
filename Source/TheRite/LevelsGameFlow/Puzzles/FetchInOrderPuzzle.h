//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FetchInOrderPuzzle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFetchPuzzleCompleted);

class ATargetPoint;
class ALightsTheRite;
class AInteractor;
class AAlex;

UCLASS()
class THERITE_API AFetchInOrderPuzzle : public AActor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AFetchInOrderPuzzle();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnFetchPuzzleCompleted OnPuzzleComplete;
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	bool IsActive() const;

	void SetPuzzleState(bool NewPuzzleState);
	void ActivatePuzzle();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	bool bActive;
	
	bool bFirstInteraction = true;
	
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	int MaxObjectsPerRound;
	
	int TotalPuzzleSteps = 0;
	
	float OffsetLightsOn;
	
	//-------- Audio
	UPROPERTY(EditAnywhere, Category = Audio, meta=(AllowPrivateAccess = true))
	USoundBase* SFX_CorrectInteraction;
	
	UPROPERTY(EditAnywhere, Category = Audio, meta=(AllowPrivateAccess = true))
	USoundBase* SFX_WrongInteraction;
	
	//-------- Lights
	UPROPERTY(EditAnywhere, Category = Lights, meta=(AllowPrivateAccess = true))
	TArray<ALightsTheRite*> AllLights;
	
	//-------- Target Points
	UPROPERTY(EditAnywhere, Category = Position, meta=(AllowPrivateAccess = true))
	TArray<ATargetPoint*> PossiblePosition;
	
	TArray<ATargetPoint*> AUXPossiblePosition;
	
	//-------- TimeLine
	FTimerHandle LightsOn_TimerHandle;
	FTimerDelegate LightsOn_TimerDelegate;

	//---------------------------------------- In game Objects
	UPROPERTY(EditAnywhere, Category = Objects)
	TArray<AInteractor*> RegularObjects;
	
	UPROPERTY(EditAnywhere, Category = Objects, meta=(ToolTip = "Objects should be in the desired order to interact being 0 first to interact"))
	TArray<AInteractor*> CorrectObjects;
	
	TArray<AInteractor*> AllObjects;
	TArray<AInteractor*> AuxCorrectObjects;

	TMap<AInteractor*, FVector> map;
	
	AAlex* Player;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void InteractionFeedBack();
	
	void LightsOut();
	void LightsOn();

	void ResetObjects();
	
	UFUNCTION()
	void ResetPuzzle(class AInteractor* Interactable);
	
	UFUNCTION()
	void CheckNextPuzzleStep(class AInteractor* Interactable);
	
	UFUNCTION()
	void NextStep();
	
	UFUNCTION()
	void PuzzleComplete();

	void ReLocateObjects();

	void RemoveFirstRightObjects();
};