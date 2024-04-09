//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "SpectralObstacle.h"

#include "Kismet/GameplayStatics.h"

ASpectralObstacle::ASpectralObstacle()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	NiagaraSystem = CreateDefaultSubobject<UNiagaraComponent>("Niagara System");

	NiagaraSystem->SetupAttachment(BoxCollider);
}

void ASpectralObstacle::BeginPlay()
{
	Super::BeginPlay();
}

void ASpectralObstacle::BeginDestroy()
{
	Super::BeginDestroy();
	UGameplayStatics::SpawnSoundAtLocation(this, SpectralSound, GetActorLocation());
	
}

void ASpectralObstacle::ObstacleDestroy()
{
	
	Destroy();
}
