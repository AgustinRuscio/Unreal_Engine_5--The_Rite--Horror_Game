//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	AClockLevelDrawersPuzzle();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Construction")
	TArray<ASpectralWrittings*> KeySpectralWrittings;

	UPROPERTY(EditAnywhere, Category = "Construction")
	TArray<ASpectralWrittings*> OtherSpectralWrittings;	

	UPROPERTY(EditAnywhere, Category = "Construction")
	ASpectralObstacle* DestroyableSpectralIbstacle;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnKeySpectralWritingUsed(AInteractor* interactor);
};