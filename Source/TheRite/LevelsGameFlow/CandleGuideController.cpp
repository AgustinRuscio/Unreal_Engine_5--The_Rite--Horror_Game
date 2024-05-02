//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "CandleGuideController.h"
#include "TheRite/AmbientObjects/Candle.h"
#include "TheRite/Interactuables/Interactor.h"

ACandleGuideController::ACandleGuideController()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void ACandleGuideController::BeginPlay()
{
	Super::BeginPlay();
	
	MyInteractor->OnInteractionTrigger.AddDynamic(this, &ACandleGuideController::GuideChange);
}

void ACandleGuideController::GuideChange(AInteractor* interactor)
{
	TurnOffPrevCandles();

	TurnOnNextCandles();
}

void ACandleGuideController::TurnOffPrevCandles()
{
	if(PlaceGuideCandles.Num() == 0) return;
	
	for (auto Element : PlaceGuideCandles)
	{
		Element->TurnOff();
	}
}

void ACandleGuideController::TurnOnNextCandles()
{
	if(NextPlaceGuideCandles.Num() == 0) return;

	for (auto Element : NextPlaceGuideCandles)
	{
		Element->TurnOn();
	}
}