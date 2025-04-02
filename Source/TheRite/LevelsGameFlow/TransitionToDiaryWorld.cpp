//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "TransitionToDiaryWorld.h"
#include "InOrdenSelectionPuzzleFlow.h"
#include "TheRite/Interactuables/SpectralObstacle.h"

//----------------------------------------------------------------------------------------------------------------------
ATransitionToDiaryWorld::ATransitionToDiaryWorld()
{
 	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ATransitionToDiaryWorld::BeginPlay()
{
	Super::BeginPlay();
	
	InOrderPuzzleFlow->OnPuzzleFinished.AddDynamic(this, &ATransitionToDiaryWorld::OnPuzzleFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void ATransitionToDiaryWorld::OnPuzzleFinished()
{
	Obstacle->ObstacleDestroy();
}