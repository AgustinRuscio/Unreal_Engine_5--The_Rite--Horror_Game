//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "PickeableInventorySlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "TheRite/Widgets/Inventory.h"
#include "TheRite/Widgets/WidgetsElements/InvenotryOnlyItem.h"

namespace {
	AInvenotryOnlyItem* TempItem;
}

//----------------------------------------------------------------------------------------------------------------------
bool UPickeableInventorySlot::Initialize()
{
	if (!Super::Initialize()) return false;

	if (ButtonSlot)
	{
		ButtonSlot->OnClicked.AddDynamic(this, &UPickeableInventorySlot::OnButtonPressed);
		ButtonSlot->SetIsEnabled(false);
	}

	return true; 
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::SetUpInventory(UInventory* NewInventory)
{
	Inventory = NewInventory;
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::SetIsBeingMoved(bool NewState)
{
	bIsBeingMoved = NewState;
	ButtonSlot->SetIsEnabled(NewState ? NewState : bIsOccupied);
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::SetCombining(bool NewState)
{
	bisCombining = NewState;
	ButtonSlot->SetIsEnabled(NewState ? NewState : bIsOccupied);
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::SetUpSlot(const FInventoryItemData& ItemData)
{
 	SetOccupiedState(true);

	ItemInfo = ItemData;

	SetImage(ItemData.DisplayImage);

}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::ClearSlot()
{
	SetOccupiedState(false);

	ItemInfo = FInventoryItemData();

	SetImage(EmptyImage);
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::RemoveItemFromInventory()
{
	if(!ItemInfo.bIsRemovable) return;

	Inventory->RemoveItem(ItemInfo);
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::OnButtonPressed()
{
	if (bIsBeingMoved)
		MovingLogic();
	else if(bisCombining)
		CombineLogic();
	else
		SelectingLogic();
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::MovingLogic()
{
	if (Inventory->GetCurrentSlot() == this)
	{
		Inventory->SetMovingMode(false);
	}
	else
	{
		auto TempInfo = Inventory->GetCurrentSlot()->GetSlotDataInfo();

		if (bIsOccupied)
		{
			Inventory->GetCurrentSlot()->SetUpSlot(ItemInfo);
		}
		else
		{
			Inventory->GetCurrentSlot()->ClearSlot();
		}

		SetUpSlot(TempInfo);

		Inventory->SetMovingMode(false);

	}
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::CombineLogic()
{
	if (Inventory->GetCurrentSlot() == this)
	{
		Inventory->SetCombineMode(false);
	}
	else
	{
		if(ItemInfo.CombineID != Inventory->GetCurrentSlot()->GetSlotDataInfo().ItemId)
		{
			Inventory->SetCombineMode(false);
		}
		else
		{
			TempItem = GetWorld()->SpawnActor<AInvenotryOnlyItem>(ItemInfo.ResultItem);

			Inventory->RemoveItem(Inventory->GetCurrentSlot()->GetSlotDataInfo());
			RemoveItemFromInventory();

			Inventory->SetCombineMode(false);

			Inventory->PushItemToGrid(TempItem->GetSlotDataInfo());

			TempItem->Destroy();
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::SelectingLogic()
{
	if (Inventory->GetCurrentSlot() != this)
	{
		Inventory->SetSlotInfo(ItemInfo, this);
		Inventory->ClearSlotOptions();
	}
	else
	{
		Inventory->ConfigSlotOptions(this);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::SetImage(UTexture* DisplayImage) const
{
	FSlateBrush Brush;
	Brush.SetResourceObject(DisplayImage);

	ItemImage->SetBrush(Brush);
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::SetOccupiedState(bool NewState)
{
	bIsOccupied = NewState;
	bIsBeingMoved = false;
	ButtonSlot->SetIsEnabled(NewState);
}