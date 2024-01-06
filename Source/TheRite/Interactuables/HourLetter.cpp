#include "HourLetter.h"

AHourLetter::AHourLetter()
{
 	PrimaryActorTick.bCanEverTick = true;

	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Letter mesh");
	RootComponent = LetterMesh;
}

void AHourLetter::Interaction()
{
	OnAction.Broadcast();
	Destroy();
}
