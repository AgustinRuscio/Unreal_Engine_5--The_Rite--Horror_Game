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
	PlayerInventory->PushItemToGrid(ItemData);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::RemoveItem(PickableItemsID id)
{
	PlayerInventory->RemoveItem(id);
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