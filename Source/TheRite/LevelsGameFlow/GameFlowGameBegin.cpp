//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "GameFlowGameBegin.h"

AGameFlowGameBegin::AGameFlowGameBegin()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AGameFlowGameBegin::BeginPlay()
{
	Super::BeginPlay();
}

void AGameFlowGameBegin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}