

#include "GameFlowDiaryLevelOtherWorld.h"
#include "InOrdenSelectionPuzzleFlow.h"

AGameFlowDiaryLevelOtherWorld::AGameFlowDiaryLevelOtherWorld()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void AGameFlowDiaryLevelOtherWorld::BeginPlay()
{
	Super::BeginPlay();
	InOrderPOuzzleController->OnPuzzleFinished.AddDynamic(this, &AGameFlowDiaryLevelOtherWorld::EndGame);
}

void AGameFlowDiaryLevelOtherWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameFlowDiaryLevelOtherWorld::EndGame()
{
}

