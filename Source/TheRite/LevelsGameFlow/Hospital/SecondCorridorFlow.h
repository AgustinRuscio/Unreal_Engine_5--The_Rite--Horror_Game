//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "SecondCorridorFlow.generated.h"

UCLASS()
class THERITE_API ASecondCorridorFlow : public AActor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ASecondCorridorFlow();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnyWhere, Category = "Settings")
	FVector LocationToAddToLightsPuzzleInteractor;

	UPROPERTY(EditAnywhere, Category = "Puzzles")
	class ALightsPuzzle* LightsPuzzle;

	UPROPERTY(EditAnywhere, Category = "Puzzles")
	class AInteractor* KeyLightsObject;

	FTimeline TimeLineMoveInteractor;

	UPROPERTY(EditAnywhere, Category = "TimeLine")
	UCurveFloat* CurveFloatMoveLightsKeyInteractor;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnLightsPuzzleCompleted();
	void OnLightsPuzzleCompletedFeedBack();


	void MoveInteractorTick(float DeltaSeconds);
	void MoveInteractorFinished(float DeltaSeconds);
};