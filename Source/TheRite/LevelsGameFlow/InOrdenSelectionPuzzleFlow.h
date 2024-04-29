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

UCLASS()
class THERITE_API AInOrdenSelectionPuzzleFlow : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category="Settings")
	TArray<ATargetPoint*> AltarPositions;

	int8 MaxStatuatte;
	int8 StatuatteIndex;

	UPROPERTY(EditAnywhere, Category="Settings")
	USoundBase* AlexAudio;
	
	bool bEnableDoOnce = true;
	
	UFUNCTION()
	void AddStatuette(AInteractor* currentStatuette);

	void CheckStatuetteOrder();
	void PuzzleFailure();
protected:
	virtual void BeginPlay() override;

public:	
	AInOrdenSelectionPuzzleFlow();

	UPROPERTY(EditAnywhere, Category = "In game objects")
	TArray<AStatuette*> InGameStatuettes;
	
	TArray<AStatuette*> StatuettsAuxiliaryArray;

	FOnPuzzleFinished OnPuzzleFinished;
};