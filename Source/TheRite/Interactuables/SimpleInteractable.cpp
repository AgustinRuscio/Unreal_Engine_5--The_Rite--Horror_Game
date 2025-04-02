//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "SimpleInteractable.h"
#include <Kismet/GameplayStatics.h>

//----------------------------------------------------------------------------------------------------------------------
ASimpleInteractable::ASimpleInteractable()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = MeshComponent;
	
	bDestroy = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleInteractable::Interaction()
{
	if(!bCanInteract) return;
	
	Super::Interaction();

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());

	if(!bDestroy) return;

	Destroy();
}