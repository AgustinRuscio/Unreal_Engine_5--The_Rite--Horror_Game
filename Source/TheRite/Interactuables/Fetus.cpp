//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Fetus.h"
#include "NiagaraSystem.h"
#include "Components/ArrowComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "TheRite/Components/FadeObjectComponent.h"

//*****************************Public**********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------
bool AFetus::GetIsCorrectFetus() const
{
	return bIsCorrectFetus;
}

//----------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------
void AFetus::ResetFetus()
{
	SetActorLocation(InitialPosition);
}

//----------------------------------------------------------------------------------------------------------------------
void AFetus::StartAudioComponent()
{
	AudioComponent->Play();
}

void AFetus::BeginPlay()
{
	Super::BeginPlay();
	
	OnFadeDeActivate();
}

//*****************************Private**********************************************
//**********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AFetus::SetFaderValues()
{
	FadeComponent = CreateDefaultSubobject<UFadeObjectComponent>("Fader Component");
	
	OnActivate.AddDynamic(this, &AFetus::OnFadeActivated);
	OnDeactivate.AddDynamic(this, &AFetus::OnFadeDeactivate);
	
	SetActor(this);
	SetFaderComponent(FadeComponent);
	
	FadeComponent->DeActivateFade();
	OnFadeDeactivate();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetus::OnFadeActivated()
{
	bCanInteract = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AFetus::OnFadeDeactivate()
{
	bCanInteract = false;
}