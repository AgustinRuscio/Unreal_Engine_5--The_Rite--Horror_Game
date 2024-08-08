//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "DoorSlapper.h"
#include "Components/BoxComponent.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Door.h"

ADoorSlapper::ADoorSlapper()
{
 	PrimaryActorTick.bCanEverTick = true;
	ClosingTrigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
}

void ADoorSlapper::BeginPlay()
{
	Super::BeginPlay();
	ClosingTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADoorSlapper::SlapDoor);
}

void ADoorSlapper::Activate()
{
	bActive = true;
}

void ADoorSlapper::Deactivate()
{
	bActive = false;
}

void ADoorSlapper::SlapDoor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bActive) return;
	
	if(!Cast<AAlex>(OtherActor)) return;

	for (auto Element : DoorsToSlap)
	{
		Element->HardClosing();
		Element->SetLockedState(true);
	}
	
	Destroy();
}
