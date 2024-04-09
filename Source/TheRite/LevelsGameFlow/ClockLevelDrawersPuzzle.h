//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "LevelSequence.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/DoorKey.h"
#include "TheRite/Interactuables/BaseDrawer.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "Engine/TargetPoint.h"
#include "TheRite/Interactuables/SpectralObstacle.h"
#include "TheRite/Interactuables/SpectralWrittings.h"
#include "ClockLevelDrawersPuzzle.generated.h"

UCLASS()
class THERITE_API AClockLevelDrawersPuzzle : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, Category = "Construction")
	ASpectralWrittings* KeySpectralWrittings;

	UPROPERTY(EditAnywhere, Category = "Construction")
	TArray<ASpectralWrittings*> OtherSpectralWrittings;	

	UPROPERTY(EditAnywhere, Category = "Construction")
	ASpectralObstacle* DestroyableSpectralIbstacle;

	
	UFUNCTION()
	void OnKeySpectralWrittingUsed();
	


	
protected:
	virtual void BeginPlay() override;

public:	
	AClockLevelDrawersPuzzle();
};