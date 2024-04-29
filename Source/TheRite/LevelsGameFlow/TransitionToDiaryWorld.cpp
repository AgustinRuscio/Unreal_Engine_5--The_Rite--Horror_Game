//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "TransitionToDiaryWorld.h"
#include "InOrdenSelectionPuzzleFlow.h"
#include "TheRite/Interactuables/SpectralObstacle.h"

ATransitionToDiaryWorld::ATransitionToDiaryWorld()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void ATransitionToDiaryWorld::OnPuzzleFinished()
{
	Obstacle->ObstacleDestroy();
}

void ATransitionToDiaryWorld::BeginPlay()
{
	Super::BeginPlay();
	
	InOrderPuzzleFlow->OnPuzzleFinished.AddDynamic(this, &ATransitionToDiaryWorld::OnPuzzleFinished);
}