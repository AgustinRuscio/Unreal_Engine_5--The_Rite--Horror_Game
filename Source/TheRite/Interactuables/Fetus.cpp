//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Fetus.h"
#include "NiagaraSystem.h"
#include "Components/ArrowComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "TheRite/Components/FadeObjectComponent.h"

AFetus::AFetus()
{
	PrimaryActorTick.bCanEverTick = true;

	FetusMesh = CreateDefaultSubobject<UStaticMeshComponent>("Fetus Mesh");
	
	BloodSpawnLoscation = CreateDefaultSubobject<UArrowComponent>("Arrow");
	BloodSpawnLoscation->SetupAttachment(FetusMesh);
	
	InitialPosition = GetActorLocation();
	
	SetFaderValues();
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

//---------------- Status Methods
void AFetus::ResetFetus()
{
	SetActorLocation(InitialPosition);
}
void AFetus::SetFaderValues()
{
	FadeComponent = CreateDefaultSubobject<UFadeObjectComponent>("Fader Component");
	
	SetActor(this);
	SetFaderComponent(FadeComponent);

	OnActivate.AddDynamic(this, &AFetus::OnFadeActivated);
	OnDeactivate.AddDynamic(this, &AFetus::OnFadeDeactivate);

}

void AFetus::OnFadeActivated()
{
	bCanInteract = true;
}

void AFetus::OnFadeDeactivate()
{
	bCanInteract = false;
}