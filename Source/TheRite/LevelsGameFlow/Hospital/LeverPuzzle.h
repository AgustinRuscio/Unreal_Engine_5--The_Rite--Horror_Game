//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeverPuzzle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleCompleted);

UCLASS()
class THERITE_API ALeverPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ALeverPuzzle();
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	FOnPuzzleCompleted OnPuzzleCompleted;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	UFUNCTION()
	void PuzzleFailed();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bPuzzleCorrect;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	int8 CorrectAmount;

	int8 InteractionCounter;

	UPROPERTY(EditDefaultsOnly, Category = Feedback)
	USoundBase* PuzzleFailSound;
	
	UPROPERTY(EditAnywhere)
	TArray<class ALever*> AllLevels;

	TArray<class ALever*> AuxUsedLevers;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckLever(class AInteractor* interactor);

	UFUNCTION()
	void DisableLevers(class ALever* interactor);
	UFUNCTION()
	void EnableLevers(class ALever* interactor);

	void CheckPuzzleEnd();

	void PuzzleCompleted();
};