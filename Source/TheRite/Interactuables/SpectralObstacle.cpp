#include "SpectralObstacle.h"

#include "Kismet/GameplayStatics.h"

ASpectralObstacle::ASpectralObstacle()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	NiagaraSystem = CreateDefaultSubobject<UNiagaraComponent>("Niagara System");

	NiagaraSystem->SetupAttachment(BoxCollider);
}

void ASpectralObstacle::OnDestroy()
{
	UGameplayStatics::SpawnSoundAtLocation(this, SpectralSound, GetActorLocation());
	Destroy();
}