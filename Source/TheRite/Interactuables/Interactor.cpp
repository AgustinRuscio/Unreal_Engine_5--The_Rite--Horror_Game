#include "Interactor.h"

AInteractor::AInteractor()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AInteractor::Interaction()
{
	OnInteractionTrigger.Broadcast();
}

bool AInteractor::IsPickable() const
{
	return bIsPickeable;
}

FString AInteractor::GetItemName() const
{
	return DisplayName;
}

FString AInteractor::GetItemID() const
{
	return ItemID;
}

USoundBase* AInteractor::GetSound()
{
	if(bWillSound)
		return AudioToPlay;
	else
		return nullptr;
}
