#include "Interactor.h"

AInteractor::AInteractor()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AInteractor::Interaction()
{
	OnInteractionTrigger.Broadcast();
}


USoundBase* AInteractor::GetSound()
{
	if(bWillSound)
		return AudioToPlay;
	else
		return nullptr;
}