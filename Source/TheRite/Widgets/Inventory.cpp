//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "Inventory.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "TheRite/Widgets/PickeableInventorySlot.h"
#include "Styling/SlateBrush.h"


//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
bool UInventory::CanRecieveItem() const
{
	for (const auto& Current : AllSlots)
	{
		if(Current->GetIsOccupied()) continue;
		return true;
	}

	return false;
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::SetSlotInfo(const FInventoryItemData& ClickedInfo, UPickeableInventorySlot* ClickedSlot)
{
	ItemName->SetText(ClickedInfo.DisplayName);
	ItemDescription->SetText(ClickedInfo.DisplayDescription);

	CurrentSlot = ClickedSlot;
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::ClearDisplayedInfo()
{
	ItemName->SetText(FText::FromString(TEXT("")));
	ItemDescription->SetText(FText::FromString(TEXT("")));
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::PushItemToGrid(const FInventoryItemData& NewPickUpData)
{
	for (const auto& Current : AllSlots)
	{
		if (Current->GetIsOccupied()) continue;

		Current->SetUpSlot(NewPickUpData);
		return;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::RemoveItem(const PickableItemsID& id)
{

	for (const auto& Current : AllSlots)
	{
		if (Current->GetSlotDataInfo().ItemId != id) continue;
		
		Current->ClearSlot();

		if(Current == CurrentSlot)
			ClearDisplayedInfo();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::NativeConstruct()
{
	for (const auto& current : SlotsPanel->GetAllChildren())
	{
		if (auto castedChild = Cast<UPickeableInventorySlot>(current))
		{
			castedChild->SetUpInventory(this);
			AllSlots.Add(castedChild);
		}
	}
}