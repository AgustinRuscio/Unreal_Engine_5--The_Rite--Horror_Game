//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
	OnInteractionTrigger.Broadcast(this);
	Destroy();
}
