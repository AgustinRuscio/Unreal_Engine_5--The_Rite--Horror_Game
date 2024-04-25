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
	
private:	

	AAlex* Player;

	UPROPERTY(EditAnywhere, Category = "States")
	ARedDoor* RedDoor;

	UPROPERTY(EditAnywhere, Category = "States")
	ASpectralWrittings* KeySpectralWrittings;

	UPROPERTY(EditAnywhere, Category = "States")
	ASpectralObstacle* RedDoorObstacle;

	UFUNCTION()
	void RedDoorOpen(AInteractor* interactor);
	
protected:
	virtual void BeginPlay() override;

public:	
	ATransitionWorldFlow();
};