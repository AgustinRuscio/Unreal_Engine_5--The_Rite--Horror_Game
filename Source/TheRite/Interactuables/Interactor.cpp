//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Interactor.h"

AInteractor::AInteractor()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AInteractor::Interaction()
{
	OnInteractionTrigger.Broadcast();
}

void AInteractor::SetCanInteract(bool newInteractionState)
{
	bCanInteract = newInteractionState;
}

bool AInteractor::IsPickable() const
{
	return bIsPickeable;
}

bool AInteractor::IsMainItem() const
{
	return bIsMainItem;
}

FString AInteractor::GetItemName() const
{
	return DisplayName;
}

PickableItemsID AInteractor::GetItemID() const
{
	return ItemID;
}

bool AInteractor::IsRemovable()
{
	return bIsRemovable;
}

TTuple<bool, FString, PickableItemsID> AInteractor::CheckRemove()
{
	TTuple<bool, FString, PickableItemsID> InteractorInfo(bIsRemovable, GetItemName(), GetItemID());
	return InteractorInfo;	
}

void AInteractor::SetPickeableSettings(bool isPickeable, FString nameToDisplay, PickableItemsID id)
{
	bIsPickeable = isPickeable;
	DisplayName = nameToDisplay;
	ItemID = id;
}

USoundBase* AInteractor::GetSound()
{
	if(bWillSound)
		return AudioToPlay;
	else
		return nullptr;
}