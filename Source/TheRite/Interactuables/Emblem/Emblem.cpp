//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "Emblem.h"

//----------------------------------------------------------------------------------------------------------------------
AEmblem::AEmblem()
{
 	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	RootComponent = MeshComponent;
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblem::Interaction()
{
	if(!bCanInteract) return;

	Super::Interaction();

	Destroy();
}