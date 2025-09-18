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
void UPickeableInventorySlot::OnButtonPressed()
{
	Inventory->SetSlotInfo(ItemInfo, this);
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

	ButtonSlot->SetIsEnabled(NewState);
}