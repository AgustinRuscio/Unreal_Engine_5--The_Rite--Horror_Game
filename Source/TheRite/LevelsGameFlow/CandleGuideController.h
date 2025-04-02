//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CandleGuideController.generated.h"

class ACandle;
class AInteractor;

UCLASS()
class THERITE_API ACandleGuideController : public AActor
{
	GENERATED_BODY()

public:	
	ACandleGuideController();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Settings")
	AInteractor* MyInteractor;

	UPROPERTY(EditAnywhere, Category = "States")
	TArray<ACandle*> PlaceGuideCandles;

	UPROPERTY(EditAnywhere, Category = "States")
	TArray<ACandle*> NextPlaceGuideCandles;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

//---------------- Action Methods
	UFUNCTION()
	void GuideChange(AInteractor* interactor);

	void TurnOffPrevCandles();
	void TurnOnNextCandles();
};