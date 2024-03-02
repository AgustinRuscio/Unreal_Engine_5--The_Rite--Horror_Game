#include "Letter.h"

ALetter::ALetter()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Letter mesh");
}

void ALetter::Interaction()	
{
	OnInteractionTrigger.Broadcast();
	OnAction.Broadcast();
	Destroy();
}