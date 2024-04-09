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
}