//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "MinutesLetter.h"

AMinutesLetter::AMinutesLetter()
{
 	PrimaryActorTick.bCanEverTick = true;

	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Letter mesh");
	RootComponent = LetterMesh;
}

void AMinutesLetter::Interaction()
{
	OnInteractionTrigger.Broadcast(this);
	OnAction.Broadcast();
	Destroy();
}