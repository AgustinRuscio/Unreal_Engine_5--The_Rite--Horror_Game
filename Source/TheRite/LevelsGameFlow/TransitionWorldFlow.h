//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
	ATransitionWorldFlow();
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void RedDoorOpen(AInteractor* interactor);
	
private:	
	UPROPERTY(EditAnywhere, Category = "States")
	ARedDoor* RedDoor;

	UPROPERTY(EditAnywhere, Category = "States")
	ASpectralWrittings* KeySpectralWrittings;

	UPROPERTY(EditAnywhere, Category = "States")
	ASpectralObstacle* RedDoorObstacle;
	
	AAlex* Player;
};