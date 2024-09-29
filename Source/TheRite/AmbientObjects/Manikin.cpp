//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Manikin.h"

//*****************************Public*******************************************
//******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AManikin::AManikin()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Object Mesh");
	
	bActive = bStartsActive;
}

//----------------------------------------------------------------------------------------------------------------------
void AManikin::Activate()
{
	bActive = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AManikin::Deactivate()
{
	bActive = false;
}

//*****************************Private*******************************************
//*******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AManikin::Tick(float DeltaTime)
{
	if(!bActive) return;

	Super::Tick(DeltaTime);
	
	if(WasRecentlyRendered(.3f)) return;
	
	ReLocateTimer += DeltaTime;
	
	if(ReLocateTimer < ReLocateColdDown) return;

	ReLocateObject();
}

//----------------------------------------------------------------------------------------------------------------------
void AManikin::ReLocateObject()
{
	ReLocateTimer = 0;

	TArray<ATargetPoint*> AuxArray;

	for (auto Element : PossiblesLocations)
	{
		if(Element->GetActorLocation().Equals(GetActorLocation())) continue;
		if(Element->WasRecentlyRendered(.3f)) continue;
		AuxArray.Add(Element);
	}
	
	int8 rand = FMath::RandRange(0, PossiblesLocations.Num()-1);
	
	SetActorLocation(PossiblesLocations[rand]->GetActorLocation());
	SetActorRotation(PossiblesLocations[rand]->GetActorRotation());
}