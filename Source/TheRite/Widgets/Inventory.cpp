#include "Inventory.h"

void UInventory::AddItemToInventory(FString itemName, FString id)
{
	for (auto Element : AllItems)
	{
		if(Element.Key == itemName)
			return;
	}
	
	TPair<FString, UStaticMesh*> addedPair;
	addedPair.Key = itemName;
	addedPair.Value = ItemsInIds[id];
	
	AllItems.Add(addedPair);
}

void UInventory::SetButtons(UButton* Next, UButton* Prev, UTextBlock* textBlock)
{
	BTN_NextItem = Next;
	BTN_PrevItem = Prev;
	TextBlockName = textBlock;
	
	BTN_NextItem->OnClicked.AddDynamic(this, &UInventory::ShowNextItem);
	BTN_PrevItem->OnClicked.AddDynamic(this, &UInventory::ShowPrevItem);
}

void UInventory::ShowNextItem()
{
	index++;
	
	if(index > AllItems.Num()-1)
		index = 0;

	CurrentPair = AllItems[index];

	
	OnInventoryChange.Broadcast(CurrentPair.Key, CurrentPair.Value);
}

void UInventory::ShowPrevItem()
{
	index--;
	
	if(index < 0)
		index = AllItems.Num()-1;

	CurrentPair = AllItems[index];

	//TextBlockName->SetText(CurrentPair.Key);
	OnInventoryChange.Broadcast(CurrentPair.Key, CurrentPair.Value);
}
