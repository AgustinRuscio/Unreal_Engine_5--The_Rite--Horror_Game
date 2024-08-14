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

private:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnKeySpectralWritingUsed(AInteractor* interactor);
	
private:
	UPROPERTY(EditAnywhere, Category = "Construction")
	TArray<ASpectralWrittings*> KeySpectralWrittings;

	UPROPERTY(EditAnywhere, Category = "Construction")
	TArray<ASpectralWrittings*> OtherSpectralWrittings;	

	UPROPERTY(EditAnywhere, Category = "Construction")
	ASpectralObstacle* DestroyableSpectralIbstacle;
};