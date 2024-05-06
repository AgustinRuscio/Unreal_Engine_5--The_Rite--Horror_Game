//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "TransitionWorldFlow.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/SpectralObstacle.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/Interactuables/RedDoor.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Interactuables/SpectralWrittings.h"

ATransitionWorldFlow::ATransitionWorldFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ATransitionWorldFlow::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));
	Player->SetPlayerOptions(true, false, false);

	KeySpectralWrittings->OnInteractionTrigger.AddDynamic(this, &ATransitionWorldFlow::RedDoorOpen);
}

void ATransitionWorldFlow::RedDoorOpen(AInteractor* interactor)
{
	RedDoor->SetCanInteract(true);
	RedDoorObstacle->ObstacleDestroy();
}