//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "InventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "TheRite/Widgets/Inventory.h"

//----------------------------------------------------------------------------------------------------------------------
UInventoryComponent::UInventoryComponent() : InventoryZOrder(2), InventoryWidgetClass(nullptr), PlayerInventory(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
bool UInventoryComponent::DoesInvetoryHasSpace() const
{
	return PlayerInventory->CanRecieveItem();
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::ToggleInventory(bool visible)
{
	visible ? PlayerInventory->AddToViewport(InventoryZOrder) : PlayerInventory->RemoveFromParent();
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::AddItem(const FInventoryItemData& ItemData)
{
	PlayerInventory->PushItemToGrid(ItemData);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::RemoveItem(const FInventoryItemData& id)
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
}