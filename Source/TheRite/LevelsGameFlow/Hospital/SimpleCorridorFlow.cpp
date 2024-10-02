//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "SimpleCorridorFlow.h"

#include "Animation/SkeletalMeshActor.h"
#include "Engine/TriggerBox.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/AmbientObjects/Manikin.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/Triggers/TimerSound.h"

//----------------------------------------------------------------------------------------------------------------------
ASimpleCorridorFlow::ASimpleCorridorFlow()
{
	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::BeginPlay()
{
	Super::BeginPlay();
	EndTiffany->GetSkeletalMeshComponent()->SetVisibility(false);
	
	BindTriggers();
	BindInteractables();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandleEnd);
	}

	if(TimerDelegateEnd.IsBound())
	{
		TimerDelegateEnd.Unbind();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::BindInteractables()
{
	EndInteractable->OnInteractionTrigger.AddDynamic(this, &ASimpleCorridorFlow::OnPuzzleFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::BindTriggers()
{
	TriggerEnableManikin->OnActorBeginOverlap.AddDynamic(this, &ASimpleCorridorFlow::OnTriggerBeginEnableAmbientInteractions);
	TriggerEnd->OnActorBeginOverlap.AddDynamic(this, &ASimpleCorridorFlow::OnTriggerBeginEnd);
	TriggerOutSideEnd->OnActorBeginOverlap.AddDynamic(this, &ASimpleCorridorFlow::OnTriggerBeginOutSideEnd);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnPuzzleFinished(AInteractor* Interactable)
{
	bPuzzleEnd = true;
	
	EndTiffany->GetSkeletalMeshComponent()->SetVisibility(true);
	TimerSound->Destroy();
	
	for (auto Element : InitialDoors)
	{
		Element->SetLockedState(false);
		Element->Open();
	}

	for (auto Element : AllLights)
	{
		Element->SetAggressiveMaterial();
		Element->ChangeLightIntensity(Element->GetIntensity() - 150.f, false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnTriggerBeginEnableAmbientInteractions(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;

	Manikin->Activate();
	TimerSound->Activate();
	
	TriggerEnableManikin->Destroy();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnTriggerBeginEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!bPuzzleEnd) return;

	// Play Audio ENd
	
	for (auto Element : AllLights)
	{
		Element->TurnOff();
		Element->SetAggressiveMaterial();
	}

	EndTiffany->Destroy();

	if(!GetWorld()->GetTimerManager().IsTimerActive(TimerHandleEnd))
	{
		TimerDelegateEnd.BindLambda([&]
		{
			for (auto Element : AllLights)
			{
				Element->TurnOn();
			}

			TriggerEnd->Destroy();
		});
		
		GetWorld()->GetTimerManager().SetTimer(TimerHandleEnd, TimerDelegateEnd, 3, false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnTriggerBeginOutSideEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!bPuzzleEnd) return;

	for (auto Element : AllLights)
	{
		Element->TurnOff();
	}
	
	for (auto Element : InitialDoors)
	{
		Element->HardClosing();
		Element->SetLockedState(true);
	}

	//Detener sonidos
	TriggerOutSideEnd->Destroy();
	Manikin->Destroy();
	Destroy();
}