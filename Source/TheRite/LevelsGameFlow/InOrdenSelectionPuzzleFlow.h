//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InOrdenSelectionPuzzleFlow.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleFinished);

class AStatuette;
class AInteractor;
class ATargetPoint;
class AAltarWhell;
class AAltar;

UCLASS()
class THERITE_API AInOrdenSelectionPuzzleFlow : public AActor
{
	GENERATED_BODY()

public:
	AInOrdenSelectionPuzzleFlow();
	
	virtual void BeginPlay() override;

private:
	//---------------- Check puzzle Methods
	bool CheckStatuttes();
	bool CheckRotation();
	
	void CheckStatuetteOrder();
	void PuzzleFailure();
	
	UFUNCTION()
	void AddStatuette(AInteractor* currentStatuette);

public:	
	FOnPuzzleFinished OnPuzzleFinished;
	
private:
	bool bEnableDoOnce = true;

	int8 MaxStatuatte;
	int8 StatuatteIndex;

	FTimerHandle OffSetInteraction;
	
	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* AlexAudio;
	
	UPROPERTY(EditAnywhere, Category="TargetPoints")
	TArray<ATargetPoint*> AltarPositions;
	
	UPROPERTY(EditAnywhere, Category = "Puzzle objects")
	TArray<AAltarWhell*> AltarWhells;
	
	UPROPERTY(EditAnywhere, Category = "Puzzle objects")
	TArray<AStatuette*> InGameStatuettes;
	TArray<AStatuette*> StatuettsAuxiliaryArray;

	UPROPERTY(EditAnywhere, Category = "Puzzle objects")
	AAltar* Altar;
};