//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "InventoryComponent.h"
#include "TheRite/Widgets/Inventory.h"
#include "TheRite/Widgets/PickeableInventorySlot.h"
#include "Components/WidgetComponent.h"


//----------------------------------------------------------------------------------------------------------------------
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::ToggleInventory(bool visible)
{
	PlayerInventory->SetVisibility(visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::AddItem(const FInventoryItemData& ItemData)
{
	UPickeableInventorySlot* NewPickUp = CreateWidget<UPickeableInventorySlot>(GetWorld(), InventorySlotWidgetClass);
	NewPickUp->SetUpSlot(ItemData);
	NewPickUp->SetUpInventory(PlayerInventory);
	PlayerInventory->PushItemToGrid(NewPickUp);

	SlotsContainer.Add(MakeTuple(NewPickUp, PlayerInventory->GetRowIndex(NewPickUp), PlayerInventory->GetColumnIndex(NewPickUp), ItemData.ItemId));
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::RemoveItem(PickableItemsID id)
{
	for (int i = 0; i < SlotsContainer.Num(); ++i)
	{
		if (SlotsContainer[i].Get<3>() != id) continue;
		PlayerInventory->RemoveItem(SlotsContainer[i].Get<0>());
		SlotsContainer.RemoveAt(i);

	}
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateInventoryWidget();
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::CreateInventoryWidget()
{
	PlayerInventory = CreateWidget<UInventory>(GetWorld(), InventoryWidgetClass);
	PlayerInventory->AddToViewport(2);
	PlayerInventory->SetVisibility(ESlateVisibility::Collapsed);
}