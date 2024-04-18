//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Statuette.h"
#include "InOrdenSelectionPuzzleFlow.generated.h"

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