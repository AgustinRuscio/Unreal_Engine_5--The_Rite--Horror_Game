//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Fetus.h"
#include "NiagaraComponent.h"

AFetus::AFetus()
{
	PrimaryActorTick.bCanEverTick = true;

	FetusMesh = CreateDefaultSubobject<UStaticMeshComponent>("Feus Mesh");
	NiagaraSytem_Blood = CreateDefaultSubobject<UNiagaraComponent>("Niagara System");

	NiagaraSytem_Blood->SetupAttachment(FetusMesh);
}

//---------------- System Class Methods
void AFetus::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFetus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFetus::Interaction()
{
	if(!bCanInteract) return;

	NiagaraSytem_Blood->Activate();
}