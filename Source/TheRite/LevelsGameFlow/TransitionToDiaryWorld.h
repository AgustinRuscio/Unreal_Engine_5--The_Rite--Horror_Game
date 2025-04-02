//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ATransitionToDiaryWorld();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere)
	AInOrdenSelectionPuzzleFlow* InOrderPuzzleFlow;

	UPROPERTY(EditAnywhere)
	ASpectralObstacle* Obstacle;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnPuzzleFinished();
};