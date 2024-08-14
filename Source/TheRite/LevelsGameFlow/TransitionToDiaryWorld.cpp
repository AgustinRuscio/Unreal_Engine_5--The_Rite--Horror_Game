//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "TransitionToDiaryWorld.h"
#include "InOrdenSelectionPuzzleFlow.h"
#include "TheRite/Interactuables/SpectralObstacle.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ATransitionToDiaryWorld::ATransitionToDiaryWorld()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//*****************************Private*********************************************
//*********************************************************************************

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