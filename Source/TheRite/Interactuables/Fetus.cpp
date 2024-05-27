//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Fetus.h"
#include "NiagaraComponent.h"

AFetus::AFetus()
{
	PrimaryActorTick.bCanEverTick = true;

	FetusMesh = CreateDefaultSubobject<UStaticMeshComponent>("Fetus Mesh");
	NiagaraSytem_Blood = CreateDefaultSubobject<UNiagaraComponent>("Niagara System");

	NiagaraSytem_Blood->SetupAttachment(FetusMesh);
}

//---------------- System Class Methods
void AFetus::Interaction()
{
	if(!bCanInteract) return;

	NiagaraSytem_Blood->Activate();

	if (!GetWorld()->GetTimerManager().IsTimerActive(Timer_LightsOut))
	{
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([&]
		{
			bIsCorrectFetus ? OnCorrectFetus.Broadcast() : OnWrongFetus.Broadcast();
		});
		
		GetWorld()->GetTimerManager().SetTimer(Timer_LightsOut, timerDelegate, ParticleDuration, false);
	}
}

void AFetus::ResetFetus()
{
	NiagaraSytem_Blood->Deactivate();
	NiagaraSytem_Blood->ResetSystem();
}