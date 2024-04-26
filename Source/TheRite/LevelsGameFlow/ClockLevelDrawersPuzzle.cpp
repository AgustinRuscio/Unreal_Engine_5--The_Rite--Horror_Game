//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ClockLevelDrawersPuzzle.h"
#include "TheRite/Interactuables/SpectralObstacle.h"
#include "TheRite/Interactuables/SpectralWrittings.h"
#include "TheRite/Interactuables/Interactor.h"

AClockLevelDrawersPuzzle::AClockLevelDrawersPuzzle()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AClockLevelDrawersPuzzle::BeginPlay()
{
	Super::BeginPlay();

	KeySpectralWrittings->OnInteractionTrigger.AddDynamic(this, &AClockLevelDrawersPuzzle::OnKeySpectralWrittingUsed);
}

void AClockLevelDrawersPuzzle::OnKeySpectralWrittingUsed(AInteractor* interactor)
{
	DestroyableSpectralIbstacle->ObstacleDestroy();

	if(OtherSpectralWrittings.Num() == 0) return;
	
	for (auto writtings : OtherSpectralWrittings)
	{
		writtings->Discovered();
	}
}