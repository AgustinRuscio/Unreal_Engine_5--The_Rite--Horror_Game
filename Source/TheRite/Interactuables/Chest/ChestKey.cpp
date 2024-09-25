//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "ChestKey.h"

#include "Chest.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
AChestKey::AChestKey()
{
 	PrimaryActorTick.bCanEverTick = true;
	
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