//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "TransitionWorldFlow.h"

#include "Kismet/GameplayStatics.h"

ATransitionWorldFlow::ATransitionWorldFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
}


void ATransitionWorldFlow::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));

	Player->SetPlayerStats(true, false);

	KeySpectralWrittings->OnInteractionTrigger.AddDynamic(this, &ATransitionWorldFlow::RedDoorOpen);
}

void ATransitionWorldFlow::RedDoorOpen(AInteractor* interactor)
{
	RedDoor->SetCanInteract(true);
	RedDoorObstacle->ObstacleDestroy();
}