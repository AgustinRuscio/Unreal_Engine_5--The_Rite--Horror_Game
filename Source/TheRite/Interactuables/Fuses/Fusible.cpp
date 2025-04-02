//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "Fusible.h"
#include "FuseBox.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
AFusible::AFusible()
{
	PrimaryActorTick.bCanEverTick = false;
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