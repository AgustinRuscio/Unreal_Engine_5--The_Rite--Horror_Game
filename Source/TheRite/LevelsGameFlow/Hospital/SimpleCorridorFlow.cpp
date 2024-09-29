//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "SimpleCorridorFlow.h"

#include "Components/BoxComponent.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/AmbientObjects/Manikin.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/Interactor.h"

//----------------------------------------------------------------------------------------------------------------------
ASimpleCorridorFlow::ASimpleCorridorFlow()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TriggerEnableManikin = CreateDefaultSubobject<UBoxComponent>("Manikin Box Component");
	TriggerEnableManikin->SetUsingAbsoluteLocation(true);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerEnableManikin->OnComponentBeginOverlap.AddDynamic(this, &ASimpleCorridorFlow::OnTriggerBeginEnableManikin);

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
void ASimpleCorridorFlow::OnTriggerBeginEnableManikin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AAlex>(OtherActor)) return;

	Manikin->Activate();

	TriggerEnableManikin->DestroyComponent();
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
		Element->ChangeLightIntensity(Element->GetIntensity() - 150.f, false);
	}
}