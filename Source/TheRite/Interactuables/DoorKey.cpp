#include "DoorKey.h"

#include "Kismet/GameplayStatics.h"

ADoorKey::ADoorKey()
{
 	PrimaryActorTick.bCanEverTick = true;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Key Mesh");
	RootComponent = KeyMesh;

	PointLight = CreateDefaultSubobject<UPointLightComponent>("Point light");
	PointLight->SetupAttachment(KeyMesh);
	
	KeyWidget = CreateDefaultSubobject<UKeyWidget>("Key Widget");
}

void ADoorKey::Interaction()
{
	if(!bKeyReady) return;

	 //OnInteractionTrigger.Broadcast();
	
	UGameplayStatics::SpawnSound2D(this, VoiceSound);

	OnKeyCollected.Broadcast();
	MyDoor->ObteinKey();
	
	UGameplayStatics::SpawnSoundAtLocation(this, SFXGrabItem,GetActorLocation());

	KeyMesh->SetVisibility(false, false);
	KeyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	KeyWidget->SetVisibility(ESlateVisibility::Visible);
	
	if (!GetWorldTimerManager().IsTimerActive(timer))
		GetWorldTimerManager().SetTimer(timer, this, &ADoorKey::TimeOver, 2.0f, false);
}

void ADoorKey::SetZone(FString NewZoneName)
{
	DoorZoneName = NewZoneName;
	
	KeyWidget->SetKeyZoneText(DoorZoneName);
}

void ADoorKey::SetDoor(ADoor* NewDoor)
{
	MyDoor = NewDoor;
}

void ADoorKey::TimeOver()
{
	KeyWidget->SetVisibility(ESlateVisibility::Hidden);
	Destroy();
}

void ADoorKey::BeginPlay()
{
	Super::BeginPlay();
	
	KeyWidget = CreateWidget<UKeyWidget>(GetWorld(), KeyUI);
	KeyWidget->AddToViewport();
	KeyWidget->SetVisibility(ESlateVisibility::Hidden);

	KeyWidget->SetKeyZoneText(DoorZoneName);
}

