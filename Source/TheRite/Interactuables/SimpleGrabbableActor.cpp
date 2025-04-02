//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "SimpleGrabbableActor.h"

//----------------------------------------------------------------------------------------------------------------------
ASimpleGrabbableActor::ASimpleGrabbableActor()
{
 	PrimaryActorTick.bCanEverTick = false;

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

//----------------------------------------------------------------------------------------------------------------------
void ASimpleGrabbableActor::Dissapear()
{
	bCanInteract = false;
	MeshComponent->SetVisibility(false);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleGrabbableActor::Appear()
{
	bCanInteract = true;
	MeshComponent->SetVisibility(true);
}