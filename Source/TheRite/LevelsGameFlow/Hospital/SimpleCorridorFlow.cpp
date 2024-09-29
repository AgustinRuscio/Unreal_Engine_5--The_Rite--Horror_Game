//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "SimpleCorridorFlow.h"

#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/Interactor.h"

//----------------------------------------------------------------------------------------------------------------------
ASimpleCorridorFlow::ASimpleCorridorFlow()
{
	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::BeginPlay()
{
	Super::BeginPlay();

	BindInteractables();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::BindInteractables()
{
	EndInteractable->OnInteractionTrigger.AddDynamic(this, &ASimpleCorridorFlow::OnPuzzleFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnPuzzleFinished(AInteractor* Interactable)
{
	for (auto Element : InitialDoors)
	{
		Element->SetLockedState(false);
		Element->Open();
	}

	for (auto Element : AllLights)
	{
		Element->SetAggressiveMaterial();
	}
}