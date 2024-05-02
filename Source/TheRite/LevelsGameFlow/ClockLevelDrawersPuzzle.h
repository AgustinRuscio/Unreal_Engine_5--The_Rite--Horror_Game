//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClockLevelDrawersPuzzle.generated.h"


class ASpectralWrittings;
class ASpectralObstacle;
class AInteractor;

UCLASS()
class THERITE_API AClockLevelDrawersPuzzle : public AActor
{
	GENERATED_BODY()

public:
	AClockLevelDrawersPuzzle();
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnKeySpectralWrittingUsed(AInteractor* interactor);
	
private:
	UPROPERTY(EditAnywhere, Category = "Construction")
	ASpectralWrittings* KeySpectralWrittings;

	UPROPERTY(EditAnywhere, Category = "Construction")
	TArray<ASpectralWrittings*> OtherSpectralWrittings;	

	UPROPERTY(EditAnywhere, Category = "Construction")
	ASpectralObstacle* DestroyableSpectralIbstacle;
};