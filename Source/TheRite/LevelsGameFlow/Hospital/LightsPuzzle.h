//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightsPuzzle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleComplete);

UCLASS()
class THERITE_API ALightsPuzzle : public AActor
{
	GENERATED_BODY()
	
	public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ALightsPuzzle();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnPuzzleComplete OnPuzzleComplete;

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnyWhere, Category = "Settings")
	TArray<class ALightsPortrait*> PortraitsInPuzzle;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckPuzzleState();

	void PuzzleCompleted();
};