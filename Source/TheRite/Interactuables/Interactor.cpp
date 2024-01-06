#include "Interactor.h"

AInteractor::AInteractor()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AInteractor::Interaction()
{
	UE_LOG(LogTemp, Warning, TEXT("No interaction"));
}


USoundBase* AInteractor::GetSound()
{
	if(bWillSound)
		return AudioToPlay;
	else
		return nullptr;
}