//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InOrdenSelectionPuzzleFlow.generated.h"

class AStatuette;
class AInteractor;

UCLASS()
class THERITE_API AInOrdenSelectionPuzzleFlow : public AActor
{
	GENERATED_BODY()
	
private:
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
};