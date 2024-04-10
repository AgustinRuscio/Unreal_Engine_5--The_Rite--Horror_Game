//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "CandleGuideController.h"

ACandleGuideController::ACandleGuideController()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void ACandleGuideController::BeginPlay()
{
	Super::BeginPlay();
	
	MyInteractor->OnInteractionTrigger.AddDynamic(this, &ACandleGuideController::GuideChange);
}

void ACandleGuideController::GuideChange()
{
	if(PlaceGuideCandles.Num() > 0)
	{
		for (auto Element : PlaceGuideCandles)
		{
			Element->TurnOff();
		}
	}

	if(NextPlaceGuideCandles.Num() > 0)
	{
		for (auto Element : NextPlaceGuideCandles)
		{
			Element->TurnOn();
		}
	}
}