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

	FTimerHandle PuzzleCompleteTimerHandle;
	FTimerDelegate PuzzleCompleteTimerDelegate;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void CheckPuzzleState();

	void PuzzleCompleted();
};