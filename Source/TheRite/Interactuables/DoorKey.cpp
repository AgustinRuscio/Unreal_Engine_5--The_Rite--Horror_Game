//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "DoorKey.h"
#include "Door.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

ADoorKey::ADoorKey()
{
 	PrimaryActorTick.bCanEverTick = true;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Key Mesh");
	RootComponent = KeyMesh;

	PointLight = CreateDefaultSubobject<UPointLightComponent>("Point light");
	PointLight->SetupAttachment(KeyMesh);
}

void ADoorKey::Interaction()
{
	if(!bKeyReady) return;

	Super::Interaction();
	
	UGameplayStatics::SpawnSound2D(this, VoiceSound);

	OnKeyCollected.Broadcast();
	OnInteractionTrigger.Broadcast(this);
	
	MyDoor->ObteinKey();
	MyDoor->SetDoorKeyValues(GetItemName(), GetItemID());
	
	UGameplayStatics::SpawnSoundAtLocation(this, SFX_GrabItem,GetActorLocation());

	Destroy();
}

void ADoorKey::SetDoor(ADoor* NewDoor)
{
	MyDoor = NewDoor;
}