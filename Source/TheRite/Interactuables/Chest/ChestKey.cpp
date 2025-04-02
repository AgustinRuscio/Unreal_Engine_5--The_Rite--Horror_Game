//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "ChestKey.h"
#include "Chest.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
AChestKey::AChestKey()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
}

//----------------------------------------------------------------------------------------------------------------------
void AChestKey::Interaction()
{
	if(!bCanInteract) return;
	
	Super::Interaction();

	UGameplayStatics::SpawnSoundAtLocation(this, SFX_GrabItem,GetActorLocation());
	MyChest->UnlockChest(GetItemName(), GetItemID());
	
	Destroy();
}