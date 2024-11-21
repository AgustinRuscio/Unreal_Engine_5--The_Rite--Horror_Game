//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FetchInOrderPuzzle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFetchPuzzleCompleted);

USTRUCT(BlueprintType)
struct FFeedbackData
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = FeedBack)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, Category = FeedBack)
	UMaterialInterface* Material;

public:
	UStaticMesh* GetNextMesh() const {return  Mesh;}
	class UMaterialInterface* GetNextMaterial() const {return  Material;}
};

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
	
	int TotalPuzzleSteps;

	int ChangingObjectsIndex;
	
	float OffsetLightsOn;
	
	//-------- Audio
	UPROPERTY(EditAnywhere, Category = Audio, meta=(AllowPrivateAccess = true))
	USoundBase* SFX_CorrectInteraction;
	
	UPROPERTY(EditAnywhere, Category = Audio, meta=(AllowPrivateAccess = true))
	USoundBase* SFX_WrongInteraction;
	
	//-------- Lights

	UPROPERTY(EditAnywhere, Category = Lights, meta=(AllowPrivateAccess = true))
	TArray<class ACustomLight*> AllLights2;
	
	//-------- Target Points
	UPROPERTY(EditAnywhere, Category = Position, meta=(AllowPrivateAccess = true))
	TArray<class ATargetPoint*> PossiblePosition;
	TArray<class ATargetPoint*> AUXPossiblePosition;
	
	TArray<class ATargetPoint*> AUXLastsCorrectedTargets;

	UPROPERTY(EditAnywhere, Category = Lights, meta=(AllowPrivateAccess = true))
	TArray<class ASpotLight*> RoomsSpotLights;
	TArray<class ASpotLight*> AUXRoomsSpotLights;

	TArray<class ASpotLight*> AUXLastsLightsUsed;
	
	UPROPERTY(EditAnywhere, Category = Lights, meta=(AllowPrivateAccess = true))
	class ASpotLight* ClueLight;
	
	
	UPROPERTY(EditAnywhere, Category = FeedBack)
	TArray<FFeedbackData> FeedbackInfo;
	
	//-------- TimeLine
	FTimerHandle LightsOn_TimerHandle;
	FTimerDelegate LightsOn_TimerDelegate;
	
	FTimerHandle LightsWit;

	//---------------------------------------- In game Objects
	UPROPERTY(EditAnywhere, Category = Objects)
	TArray<class AInteractor*> RegularObjects;
	
	UPROPERTY(EditAnywhere, Category = Objects, meta=(ToolTip = "Objects should be in the desired order to interact being 0 first to interact"))
	TArray<class AInteractor*> CorrectObjects;
	
	TArray<class AInteractor*> AllObjects;
	TArray<class AInteractor*> AuxCorrectObjects;

	UPROPERTY(EditAnywhere, Category = Objects, meta=(ToolTip = "Objects that will change material or mesh if needed"))
	TArray<class AChangingActor*> ChangingActors;
	
	TMap<class AInteractor*, FVector> MapObjectsAndLocations;

	UPROPERTY(EditAnywhere, Category = FeedBack, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<class UCameraShakeBase> CameraShake_CorrectObject;
	
	UPROPERTY(EditAnywhere, Category = FeedBack, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShake_WrongObject;
	
	class AAlex* Player;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void PrepareTargets();

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