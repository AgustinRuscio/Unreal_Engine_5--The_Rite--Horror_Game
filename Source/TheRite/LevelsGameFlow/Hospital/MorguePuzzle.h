//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MorguePuzzle.generated.h"

UCLASS()
class THERITE_API AMorguePuzzle : public AActor
{
	GENERATED_BODY()
	
public:	

	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AMorguePuzzle();

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
	UPROPERTY(EditAnywhere, Category = "Coffins")
	float NewLightIntensity = 4.f;

	UPROPERTY(EditAnywhere, Category = "Coffins")
	TArray<class ACoffin*> AllCoffins;

	UPROPERTY(EditAnywhere, Category = "Coffins")
	TArray<class ACoffin*> CorrectCoffins;

	TArray<class ACoffin*> OpenCoffins;

	UPROPERTY(EditAnywhere, Category = "Coffins")
	class ACoffin* LastCoffin;

	UPROPERTY(EditAnywhere, Category = "Feedback")
	TArray<class ACustomLight*> FeedbackLights;

	UPROPERTY(EditDefaultsOnly, Category = "Feedback")
	TArray<USoundBase*> EndPuzzleSFX;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCoffinOppened(class AInteractor* Interactor);
	void CheckPuzzleStatus();

	UFUNCTION()
	void CoffinOpened();
	void OnPuzzleCompleted();

	void PuzzleCompleteFeedBack();
};