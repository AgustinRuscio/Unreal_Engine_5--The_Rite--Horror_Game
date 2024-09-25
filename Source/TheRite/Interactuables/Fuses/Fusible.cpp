//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Fusible.h"
#include "FuseBox.h"
#include "Kismet/GameplayStatics.h"


//*****************************Public***********************************************
//***********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AFusible::AFusible()
{
	PrimaryActorTick.bCanEverTick = true;
	FusibleMesh= CreateDefaultSubobject<UStaticMeshComponent>("Fusible mesh");
}

//----------------------------------------------------------------------------------------------------------------------
void AFusible::Interaction()
{
	if(!bCanInteract) return;

	OnInteractionTrigger.Broadcast(this);
	FuseBox->GrabFusible(GetItemName(), GetItemID());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());
	
	Destroy();
}