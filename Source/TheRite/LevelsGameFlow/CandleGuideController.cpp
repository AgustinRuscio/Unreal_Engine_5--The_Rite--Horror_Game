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
	for (auto Element : PlaceGuideCandles)
	{
		if(!Element) continue;
		Element->TurnOff();
	}

	for (auto Element : NextPlaceGuideCandles)
	{
		if(!Element) continue;
		
		Element->TurnOn();
	}
}