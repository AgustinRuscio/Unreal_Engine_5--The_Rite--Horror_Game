//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Fetus.h"
#include "NiagaraSystem.h"
#include "Components/ArrowComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "TheRite/Components/FadeObjectComponent.h"

AFetus::AFetus()
{
	PrimaryActorTick.bCanEverTick = true;

	FetusMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Fetus Mesh");
	
	BloodSpawnLoscation = CreateDefaultSubobject<UArrowComponent>("Arrow");
	BloodSpawnLoscation->SetupAttachment(FetusMesh);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent->SetupAttachment(FetusMesh);
	
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

	if(bIsLetterPuzzle)
	{
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
}

//---------------- Status Methods
void AFetus::ResetFetus()
{
	SetActorLocation(InitialPosition);
}

void AFetus::StartAudioComponent()
{
	AudioComponent->Play();
}

void AFetus::SetFaderValues()
{
	OnActivate.AddDynamic(this, &AFetus::OnFadeActivated);
	OnDeactivate.AddDynamic(this, &AFetus::OnFadeDeactivate);
	
	FadeComponent = CreateDefaultSubobject<UFadeObjectComponent>("Fader Component");
	
	SetActor(this);
	SetFaderComponent(FadeComponent);
}

void AFetus::OnFadeActivated()
{
	bCanInteract = true;
}

void AFetus::OnFadeDeactivate()
{
	bCanInteract = false;
}