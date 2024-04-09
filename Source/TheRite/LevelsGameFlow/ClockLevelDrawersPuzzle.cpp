//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ClockLevelDrawersPuzzle.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"

AClockLevelDrawersPuzzle::AClockLevelDrawersPuzzle()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AClockLevelDrawersPuzzle::BeginPlay()
{
	Super::BeginPlay();

	KeySpectralWrittings->OnInteractionTrigger.AddDynamic(this, &AClockLevelDrawersPuzzle::OnKeySpectralWrittingUsed);
	
}

void AClockLevelDrawersPuzzle::OnKeySpectralWrittingUsed()
{
	DestroyableSpectralIbstacle->ObstacleDestroy();

	if(OtherSpectralWrittings.Num() == 0) return;
	
	for (auto writtings : OtherSpectralWrittings)
	{
		writtings->Discovered();
	}
}