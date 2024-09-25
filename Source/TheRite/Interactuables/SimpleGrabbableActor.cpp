//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "SimpleGrabbableActor.h"

//----------------------------------------------------------------------------------------------------------------------
ASimpleGrabbableActor::ASimpleGrabbableActor()
{
 	PrimaryActorTick.bCanEverTick = true;

	bCanInteract = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleGrabbableActor::Interaction()
{
	if(!bCanInteract) return;
	
	Super::Interaction();

	Destroy();
}