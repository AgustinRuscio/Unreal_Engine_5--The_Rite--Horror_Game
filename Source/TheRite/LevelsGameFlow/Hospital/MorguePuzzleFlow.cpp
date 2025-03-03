//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "MorguePuzzleFlow.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Engine/TargetPoint.h"
#include "Engine/StaticMeshActor.h"

//----------------------------------------------------------------------------------------------------------------------
AMorguePuzzleFlow::AMorguePuzzleFlow()
{
	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::BeginPlay()
{
	Super::BeginPlay();
	Emblem->OnInteractionTrigger.AddDynamic(this, &AMorguePuzzleFlow::OnEmblemInteraction);
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::OnEmblemInteraction(AInteractor* interactor)
{
	DeadBodyOne->SetActorTransform(DeadBodyOneTargetPoint->GetActorTransform());
	DeadBodyTwo->SetActorTransform(DeadBodyTwoTargetPoint->GetActorTransform());
}