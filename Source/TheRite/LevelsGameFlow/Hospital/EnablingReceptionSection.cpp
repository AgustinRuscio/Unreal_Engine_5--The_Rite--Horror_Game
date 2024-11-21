//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "EnablingReceptionSection.h"

#include "Kismet/GameplayStatics.h"
#include "TheRite/AmbientObjects/CustomLight.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/Interactuables/Emblem/EmblemsPlace.h"

//----------------------------------------------------------------------------------------------------------------------
AEnablingReceptionSection::AEnablingReceptionSection()
{
	PrimaryActorTick.bCanEverTick  = true;
	IntensityToAddToReceptionLight = 3; 
}

//----------------------------------------------------------------------------------------------------------------------
void AEnablingReceptionSection::BeginPlay()
{
	Super::BeginPlay();

	for (auto Element : Lights2)
	{
		Element->SetAggressiveMaterial();
	}
	
	EmblemsPlace->OnInteractionTrigger.AddDynamic(this, &AEnablingReceptionSection::OnFirstInteractionWithEmblemsPlace);
}

//----------------------------------------------------------------------------------------------------------------------
void AEnablingReceptionSection::OnFirstInteractionWithEmblemsPlace(AInteractor* Interactable)
{
	if(!EmblemsPlace->GetIsFirstInteraction()) return;
	
	OfficeDoor->SetLockedState(false);

	ChangeReceptionLightsSettings();

	EmblemsPlace->OnInteractionTrigger.RemoveDynamic(this, &AEnablingReceptionSection::OnFirstInteractionWithEmblemsPlace);

	Destroy();
}

//----------------------------------	------------------------------------------------------------------------------------
void AEnablingReceptionSection::ChangeReceptionLightsSettings()
{
	for (auto Element : Lights2)
	{
		Element->SetNormalMaterial();
		Element->ChangeLightIntensity(Element->GetIntensity() + IntensityToAddToReceptionLight, true);
	}

	UGameplayStatics::PlaySound2D(GetWorld(), ReceptionLightChanged);
}