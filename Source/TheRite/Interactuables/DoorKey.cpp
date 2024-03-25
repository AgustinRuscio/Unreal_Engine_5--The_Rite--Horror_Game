#include "DoorKey.h"

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
	OnInteractionTrigger.Broadcast();
	
	MyDoor->ObteinKey();
	
	UGameplayStatics::SpawnSoundAtLocation(this, SFXGrabItem,GetActorLocation());

	Destroy();
}


void ADoorKey::SetDoor(ADoor* NewDoor)
{
	MyDoor = NewDoor;
}

void ADoorKey::BeginPlay()
{
	Super::BeginPlay();
}

