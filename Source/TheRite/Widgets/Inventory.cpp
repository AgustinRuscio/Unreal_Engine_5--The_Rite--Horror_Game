//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "Inventory.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "TheRite/Widgets/PickeableInventorySlot.h"
#include "TheRite/Widgets/Inventory/InventorySlotOptions.h"
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
void UInventory::SetMovingMode(bool NewState)
{
	for (const auto& Current : AllSlots)
	{
		Current->SetIsBeingMoved(NewState);
	}

	if (!NewState)
	{
		WBP_InventorySlotOptions->CloseOptions();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::SetCombineMode(bool NewState)
{
	for (const auto& Current : AllSlots)
	{
		Current->SetCombining(NewState);
	}

	if (!NewState)
	{
		WBP_InventorySlotOptions->CloseOptions();
	}
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
void UInventory::RemoveItem(const FInventoryItemData& id)
{
	for (const auto& Current : AllSlots)
	{
		if (!Current->GetSlotDataInfo().DisplayName.EqualTo(id.DisplayName)) continue;
		
		Current->ClearSlot();

		if(Current == CurrentSlot)
			ClearDisplayedInfo();

		return;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::ConfigSlotOptions(UPickeableInventorySlot* SelectedSlot)
{
	WBP_InventorySlotOptions->OpenOptions(SelectedSlot);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::ClearSlotOptions()
{
	WBP_InventorySlotOptions->CloseOptions(); 
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::InspectItem(const FInventoryItemData& data)
{
	OnItemInspected.Broadcast(data);
}

//----------------------------------------------------------------------------------------------------------------------
bool UInventory::Initialize()
{
	if (!Super::Initialize()) return false;

	for (const auto& current : SlotsPanel->GetAllChildren())
	{
		if (auto castedChild = Cast<UPickeableInventorySlot>(current))
		{
			castedChild->SetUpInventory(this);
			AllSlots.Add(castedChild);
		}
	}

	return true;
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

	WBP_InventorySlotOptions->SetUpInventory(this);
	WBP_InventorySlotOptions->SetVisibility(ESlateVisibility::Collapsed);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::NativeDestruct()
{
	Super::NativeDestruct();

	SetMovingMode(false);
	SetCombineMode(false);

	WBP_InventorySlotOptions->CloseOptions();
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::ClearDisplayedInfo()
{
	ItemName->SetText(FText::FromString(TEXT("")));
	ItemDescription->SetText(FText::FromString(TEXT("")));

	CurrentSlot = nullptr;
}