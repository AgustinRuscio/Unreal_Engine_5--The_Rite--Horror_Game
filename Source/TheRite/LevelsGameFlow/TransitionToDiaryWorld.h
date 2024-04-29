//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TransitionToDiaryWorld.generated.h"

class AInOrdenSelectionPuzzleFlow;
class ASpectralObstacle;

UCLASS()
class THERITE_API ATransitionToDiaryWorld : public AActor
{
	GENERATED_BODY()
	
private:	

	UPROPERTY(EditAnywhere)
	AInOrdenSelectionPuzzleFlow* InOrderPuzzleFlow;

	UPROPERTY(EditAnywhere)
	ASpectralObstacle* Obstacle;
	
	UFUNCTION()
	void OnPuzzleFinished();
	
protected:
	virtual void BeginPlay() override;

public:	
	ATransitionToDiaryWorld();
};