//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Manikin.h"

AManikin::AManikin()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Object Mesh");
	
	bActive = bStartsActive;
}

void AManikin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bActive) return;
	
	if(WasRecentlyRendered(.3f)) return;
	
	ReLocateTimer += DeltaTime;
	
	if(ReLocateTimer < ReLocateColdDown) return;

	ReLocateObject();
}

void AManikin::Activate()
{
	bActive = true;
}

void AManikin::Deactivate()
{
	bActive = false;
}

void AManikin::ReLocateObject()
{
	ReLocateTimer = 0;

	TArray<ATargetPoint*> AuxArray;

	for (auto Array : PossiblesLocations)
	{
		if(Array->GetActorLocation().Equals(GetActorLocation())) continue;
		AuxArray.Add(Array);
	}
	
	int8 rand = FMath::RandRange(0, PossiblesLocations.Num()-1);
	
	SetActorLocation(PossiblesLocations[rand]->GetActorLocation());
	SetActorRotation(PossiblesLocations[rand]->GetActorRotation());
}
