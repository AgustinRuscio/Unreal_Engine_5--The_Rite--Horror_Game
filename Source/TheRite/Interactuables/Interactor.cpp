//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Interactor.h"
#include "TheRite/Widgets/Inventory.h"

AInteractor::AInteractor()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//---------------- Getter Methods
bool AInteractor::IsPickable() const
{
	return bIsPickeable;
}

bool AInteractor::IsMainItem() const
{
	return bIsMainItem;
}
bool AInteractor::IsRemovable()
{
	return bIsRemovable;
}

bool AInteractor::GetCanInteract()
{
	return bCanInteract;
}

FString AInteractor::GetItemName() const
{
	return DisplayName;
}

PickableItemsID AInteractor::GetItemID() const
{
	return ItemID;
}

TTuple<bool, FString, PickableItemsID> AInteractor::CheckRemove()
{
	TTuple<bool, FString, PickableItemsID> InteractorInfo(bIsRemovable, GetItemName(), GetItemID());
	return InteractorInfo;	
}

USoundBase* AInteractor::GetSound()
{
	return bWillSound ? AudioToPlay : nullptr;
}

//---------------- System Class Methods
void AInteractor::Interaction()
{
	if(!bCanInteract) return;
	OnInteractionTrigger.Broadcast(this);
}

//---------------- Setter Methods
void AInteractor::SetCanInteract(bool newInteractionState)
{
	bCanInteract = newInteractionState;
}

void AInteractor::SetCanWillSound(bool newWillSoundState)
{
	bWillSound = newWillSoundState;
}

void AInteractor::SetAudioToPlay(USoundBase* NewAudio)
{
	AudioToPlay = NewAudio;
}

void AInteractor::SetPickeableSettings(bool isPickeable, FString nameToDisplay, PickableItemsID id)
{
	bIsPickeable = isPickeable;
	DisplayName = nameToDisplay;
	ItemID = id;
}

void AInteractor::Deactivate()
{
	bCanInteract = false;
}

void AInteractor::Activate()
{
	bCanInteract = true;
}