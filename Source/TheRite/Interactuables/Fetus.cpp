//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Fetus.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

AFetus::AFetus()
{
	PrimaryActorTick.bCanEverTick = true;

	FetusMesh = CreateDefaultSubobject<UStaticMeshComponent>("Fetus Mesh");
	
	BloodSpawnLoscation = CreateDefaultSubobject<UArrowComponent>("Arrow");
	BloodSpawnLoscation->SetupAttachment(FetusMesh);
	
	InitialPosition = GetActorLocation();
}

bool AFetus::GetIsCorrectFetus()
{
	return bIsCorrectFetus;
}

//---------------- System Class Methods
void AFetus::Interaction()
{
	if(!bCanInteract) return;

	OnInteractionTrigger.Broadcast(this);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSytem_Blood, BloodSpawnLoscation->GetComponentLocation());
	
	if (!GetWorld()->GetTimerManager().IsTimerActive(Timer_LightsOut))
	{
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([&]
		{
			bIsCorrectFetus ? OnCorrectFetus.Broadcast() : OnWrongFetus.Broadcast();
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("BroadCast")));
		});
		
		GetWorld()->GetTimerManager().SetTimer(Timer_LightsOut, timerDelegate, ParticleDuration, false);
	}
}

void AFetus::ResetFetus()
{
	SetActorLocation(InitialPosition);
}