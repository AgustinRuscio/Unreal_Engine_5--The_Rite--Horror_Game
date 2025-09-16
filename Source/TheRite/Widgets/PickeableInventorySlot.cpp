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
	ItemInfo = ItemData;

	FSlateBrush Brush;
	UE::Slate::FDeprecateVector2DParameter v(1000.f, 1000.f);
	Brush.SetImageSize(v);
	Brush.SetResourceObject(ItemData.DisplayImage);

	ItemImage->SetBrush(Brush);
	ButtonSlot->SetIsEnabled(true);
}

//----------------------------------------------------------------------------------------------------------------------
void UPickeableInventorySlot::OnButtonPressed()
{
	Inventory->SetInfo(ItemInfo);
}