//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "InventorySlotOptions.h"
#include "Components/Button.h"
#include "TheRite/Widgets/Inventory.h"
#include "TheRite/Widgets/PickeableInventorySlot.h"

//----------------------------------------------------------------------------------------------------------------------
void UInventorySlotOptions::SetUpInventory(UInventory* InventoryToUse)
{
	Inventory = InventoryToUse;
}

//----------------------------------------------------------------------------------------------------------------------
void UInventorySlotOptions::OpenOptions(UPickeableInventorySlot* ClickedButton)
{
	CurrentSlot = ClickedButton;

	BTN_Remove->SetIsEnabled(CurrentSlot->GetSlotDataInfo().bIsRemovable);

	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventorySlotOptions::CloseOptions()
{
	CurrentSlot	= nullptr;
	SetVisibility(ESlateVisibility::Collapsed);
}

//----------------------------------------------------------------------------------------------------------------------
bool UInventorySlotOptions::Initialize()
{
	if(!Super::Initialize()) return false;

	if(BTN_Inspect)
		BTN_Inspect->OnPressed.AddDynamic(this, &UInventorySlotOptions::OnInspectButtonClicked);

	if (BTN_Move)
		BTN_Move->OnPressed.AddDynamic(this, &UInventorySlotOptions::OnMoveButtonClicked);

	if (BTN_Combine)
		BTN_Combine->OnPressed.AddDynamic(this, &UInventorySlotOptions::OnCombineButtonClicked);

	if (BTN_Remove)
		BTN_Remove->OnPressed.AddDynamic(this, &UInventorySlotOptions::OnRemoveButtonClicked);


	return true;
}

//----------------------------------------------------------------------------------------------------------------------
void UInventorySlotOptions::OnInspectButtonClicked()
{

}

//----------------------------------------------------------------------------------------------------------------------
void UInventorySlotOptions::OnMoveButtonClicked()
{
	Inventory->SetMovingMode(true);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventorySlotOptions::OnCombineButtonClicked()
{

}

//----------------------------------------------------------------------------------------------------------------------
void UInventorySlotOptions::OnRemoveButtonClicked()
{
	CurrentSlot->RemoveItemFromInventory();
	CloseOptions();
}