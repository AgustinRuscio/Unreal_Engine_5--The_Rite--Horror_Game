//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "ActivateIntermitetntActorTrigger.h"
#include "Components/BoxComponent.h"
#include "TheRite/AmbientObjects/IntermitentActor.h"
#include <TheRite/Characters/Alex.h>


//----------------------------------------------------------------------------------------------------------------------
AActivateIntermitetntActorTrigger::AActivateIntermitetntActorTrigger() : bActive(true), bOneUse(false)
{
	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
void AActivateIntermitetntActorTrigger::Activate()
{
	bActive = false;
}

//----------------------------------------------------------------------------------------------------------------------
void AActivateIntermitetntActorTrigger::Deactivate()
{
	bActive = false;
}

//----------------------------------------------------------------------------------------------------------------------
void AActivateIntermitetntActorTrigger::BeginPlay()
{
	Super::BeginPlay();

	ActivateTrigger->OnComponentBeginOverlap.AddDynamic(this, &AActivateIntermitetntActorTrigger::ActivateIntermitent);

}

//----------------------------------------------------------------------------------------------------------------------
void AActivateIntermitetntActorTrigger::ActivateIntermitent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bActive) return;

	if (bOneUse )
	{
		if(bWasUsed) return;

		bWasUsed = true;
	}

	if (!Cast<AAlex>(OtherActor)) return;

	for (auto Element : IntermitentsActors)
	{
		Element->ActivateIntermitent();
	}
}