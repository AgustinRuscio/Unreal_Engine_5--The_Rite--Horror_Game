//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "PickeableInventorySlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "TheRite/Widgets/Inventory.h"


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