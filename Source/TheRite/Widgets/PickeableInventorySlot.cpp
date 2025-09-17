//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "PickeableInventorySlot.h"
#include "Components/Button.h"
#include "TheRite/Widgets/Inventory.h"
#include "Components/Image.h"

//----------------------------------------------------------------------------------------------------------------------
bool UPickeableInventorySlot::Initialize()
{
	if (!Super::Initialize()) return false;

	ButtonSlot->OnClicked.AddDynamic(this, &UPickeableInventorySlot::OnButtonPressed);
	ButtonSlot->SetIsEnabled(false);

	return true; 
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::SetUpInventory(UInventory* NewInventory)
{
	Inventory = NewInventory;
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::SetUpSlot(FInventoryItemData ItemData)
{
	bIsOccupied = true;
	ItemInfo = ItemData;

	SetImage(ItemData.DisplayImage);

	ButtonSlot->SetIsEnabled(true);
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::ClearSlot()
{
	bIsOccupied = false;
	ItemInfo = FInventoryItemData();
	ButtonSlot->SetIsEnabled(false);
	SetImage(EmptyImage);
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::OnButtonPressed()
{
	Inventory->SetSlotInfo(ItemInfo, this);
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::SetImage(UTexture* DisplayImage)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(DisplayImage);

	ItemImage->SetBrush(Brush);
}
