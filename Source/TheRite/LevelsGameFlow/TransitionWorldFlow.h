//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TransitionWorldFlow.generated.h"

class AAlex;
class ARedDoor;
class ASpectralObstacle;
class ASpectralWrittings;
class AInteractor;

UCLASS()
class THERITE_API ATransitionWorldFlow : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ATransitionWorldFlow();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "States")
	ARedDoor* RedDoor;

	UPROPERTY(EditAnywhere, Category = "States")
	ASpectralWrittings* KeySpectralWrittings;

	UPROPERTY(EditAnywhere, Category = "States")
	ASpectralObstacle* RedDoorObstacle;

	AAlex* Player;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void RedDoorOpen(AInteractor* interactor);
};