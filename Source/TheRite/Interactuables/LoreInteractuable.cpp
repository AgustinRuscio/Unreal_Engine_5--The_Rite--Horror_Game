#include "LoreInteractuable.h"

#include "Kismet/GameplayStatics.h"

ALoreInteractuable::ALoreInteractuable()
{
 	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Object mesh");
	bCanInteract = true;
	bWillSound = true;
}

void ALoreInteractuable::Interaction()
{
	Super::Interaction();
	UGameplayStatics::SpawnSound2D(GetWorld(), AudioToPlay);
}