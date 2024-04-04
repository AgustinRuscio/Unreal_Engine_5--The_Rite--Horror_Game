//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "TiffanyDestroy.h"

#include "TheRite/Characters/Alex.h"

ATiffanyDestroy::ATiffanyDestroy()
{
 	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box collision");
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ATiffanyDestroy::OnOverlapBegin);
}

void ATiffanyDestroy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AAlex>(OtherActor)) return;

	NearLight->TurnOff();
	
	if (!GetWorldTimerManager().IsTimerActive(FirstTimer))
		GetWorldTimerManager().SetTimer(FirstTimer, this, &ATiffanyDestroy::FirstTimeOver, 1.2f, false);
}

void ATiffanyDestroy::FirstTimeOver()
{
	TiffanyToDestroy->Destroy();
	
	if (!GetWorldTimerManager().IsTimerActive(SecondsTimer))
		GetWorldTimerManager().SetTimer(SecondsTimer, this, &ATiffanyDestroy::SecondTimeOver, 1.0f, false);
}

void ATiffanyDestroy::SecondTimeOver()
{
	NearLight->TurnOn();
	Destroy();
}