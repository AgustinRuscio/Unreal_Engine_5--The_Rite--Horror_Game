//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Interactor.h"
#include "TheRite/Widgets/Inventory.h"

//*****************************Public***********************************************
//***********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AInteractor::AInteractor()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Getter Methods
bool AInteractor::IsPickable() const
{
	return bIsPickeable;
}

//----------------------------------------------------------------------------------------------------------------------
bool AInteractor::IsMainItem() const
{
	return bIsMainItem;
}

//----------------------------------------------------------------------------------------------------------------------
bool AInteractor::GetCanInteract() const
{
	return bCanInteract;
}

//----------------------------------------------------------------------------------------------------------------------
bool AInteractor::IsRemovable() const
{
	return bIsRemovable;
}

//----------------------------------------------------------------------------------------------------------------------
FString AInteractor::GetItemName() const
{
	return DisplayName;
}

//----------------------------------------------------------------------------------------------------------------------
PickableItemsID AInteractor::GetItemID() const
{
	return ItemID;
}

//----------------------------------------------------------------------------------------------------------------------
USoundBase* AInteractor::GetSound() const
{
	return bWillSound ? AudioToPlay : nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
TTuple<bool, FString, PickableItemsID> AInteractor::CheckRemove() const
{
	TTuple<bool, FString, PickableItemsID> InteractorInfo(bIsRemovable, GetItemName(), GetItemID());
	return InteractorInfo;	
}
#pragma endregion 

//----------------------------------------------------------------------------------------------------------------------
void AInteractor::Interaction()
{
	if(!bCanInteract) return;

	OnInteractionTrigger.Broadcast(this);
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Setter Methods
void AInteractor::SetCanInteract(bool newInteractionState)
{
	bCanInteract = newInteractionState;
}

//----------------------------------------------------------------------------------------------------------------------
void AInteractor::SetCanWillSound(bool newWillSoundState)
{
	bWillSound = newWillSoundState;
}

//----------------------------------------------------------------------------------------------------------------------
void AInteractor::SetAudioToPlay(USoundBase* NewAudio)
{
	AudioToPlay = NewAudio;
}

//----------------------------------------------------------------------------------------------------------------------
void AInteractor::SetPickeableSettings(bool isPickeable, FString nameToDisplay, PickableItemsID id)
{
	bIsPickeable = isPickeable;
	DisplayName = nameToDisplay;
	ItemID = id;
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
void AInteractor::Deactivate()
{
	bCanInteract = false;
}

//----------------------------------------------------------------------------------------------------------------------
void AInteractor::Activate()
{
	bCanInteract = true;
}