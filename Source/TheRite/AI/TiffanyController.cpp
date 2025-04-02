//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "TiffanyController.h"

//----------------------------------------------------------------------------------------------------------------------
ATiffanyController::ATiffanyController()
{
	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
UBehaviorTree* ATiffanyController::GetBehaviourTree() const
{
	return BehaviourTree;
}

//----------------------------------------------------------------------------------------------------------------------
void ATiffanyController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviourTree);
}