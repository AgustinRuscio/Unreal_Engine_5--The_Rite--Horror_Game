#include "TiffanyController.h"

void ATiffanyController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviourTree);
}

UBehaviorTree* ATiffanyController::GetBehaviourTree() const
{
	return BehaviourTree;
}
