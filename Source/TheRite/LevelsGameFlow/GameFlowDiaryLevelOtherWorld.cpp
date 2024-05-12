//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "GameFlowDiaryLevelOtherWorld.h"
#include "InOrdenSelectionPuzzleFlow.h"
#include "TheRite/Interactuables/Door.h"
#include "Engine/TriggerBox.h"
#include "TheRite/Characters/Alex.h"

AGameFlowDiaryLevelOtherWorld::AGameFlowDiaryLevelOtherWorld()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void AGameFlowDiaryLevelOtherWorld::BeginPlay()
{
	Super::BeginPlay();
	BindTriggers();
	InOrderPOuzzleController->OnPuzzleFinished.AddDynamic(this, &AGameFlowDiaryLevelOtherWorld::EndGame);
}

void AGameFlowDiaryLevelOtherWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameFlowDiaryLevelOtherWorld::EndGame()
{
}

void AGameFlowDiaryLevelOtherWorld::BindTriggers()
{
}

