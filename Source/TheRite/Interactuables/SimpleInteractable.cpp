//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "SimpleInteractable.h"

//----------------------------------------------------------------------------------------------------------------------
ASimpleInteractable::ASimpleInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = MeshComponent;
	
	bDestroy = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleInteractable::Interaction()
{
	if(!bCanInteract) return;
	
	Super::Interaction();

	if(!bDestroy) return;

	Destroy();
}