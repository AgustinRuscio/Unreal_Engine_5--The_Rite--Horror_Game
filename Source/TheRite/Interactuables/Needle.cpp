//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "Needle.h"
#include "BigClock.h"

// Sets default values
ANeedle::ANeedle()
{
	PrimaryActorTick.bCanEverTick = true;

	NeedleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Needle Mesh");
	RootComponent = NeedleMesh;
}

void ANeedle::Interaction()
{
Super::Interaction();
	ParentClock->CompleteClock();
	Destroy();
}