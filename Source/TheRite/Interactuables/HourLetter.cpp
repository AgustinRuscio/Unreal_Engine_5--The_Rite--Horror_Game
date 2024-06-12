//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "HourLetter.h"

#include "Kismet/GameplayStatics.h"

AHourLetter::AHourLetter()
{
 	PrimaryActorTick.bCanEverTick = true;

	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Letter mesh");
	RootComponent = LetterMesh;
}

void AHourLetter::Interaction()
{
	OnAction.Broadcast();
	OnInteractionTrigger.Broadcast(this);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());
	Destroy();
}