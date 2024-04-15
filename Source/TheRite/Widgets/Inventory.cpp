//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Inventory.h"

#include "Styling/SlateBrush.h"


void UInventory::AddItemToInventory(FString itemName, PickableItemsID id)
{
	for (auto Element : AllItems)
	{
		if(Element.Key == itemName)
			return;
	}

	
	TPair<FString, UMaterialInterface*> addedPair;
	
	addedPair.Key = itemName;
	addedPair.Value = ItemsInIds[id];
	
	AllItems.Add(addedPair);
}

void UInventory::RemoveItem(FString itemName, PickableItemsID id)
{
	for (auto Element : AllItems)
	{
		if(Element.Key == itemName)
		{
			TPair<FString, UMaterialInterface*> removedPair;

			removedPair.Key = itemName;
			removedPair.Value = ItemsInIds[id];

			AllItems.Remove(removedPair);
			return;
		}
	}
}

void UInventory::SetWidgetsObject(UButton* Next, UButton* Prev, UTextBlock* textBlock, UImage* imageToDisplay)
{
	BTN_NextItem = Next;
	BTN_PrevItem = Prev;
	TextBlockName = textBlock;
	OverlayImage = imageToDisplay;
	
	BTN_NextItem->OnClicked.AddDynamic(this, &UInventory::ShowNextItem);
	BTN_PrevItem->OnClicked.AddDynamic(this, &UInventory::ShowPrevItem);
}

void UInventory::OnInventoryOpen()
{
	if(AllItems.Num() == 0)
	{
		FText NewText = FText::FromString(TEXT("Empty"));
		TextBlockName->SetText(NewText);
		OverlayImage->SetVisibility(ESlateVisibility::Hidden);
		
		BTN_PrevItem->SetIsEnabled(false);
		BTN_NextItem->SetIsEnabled(false);
	}
	else
	{
		CurrentPair = AllItems[index];
		
		FText NewText = FText::FromString(CurrentPair.Key);
		TextBlockName->SetText(NewText);

		OverlayImage->SetVisibility(ESlateVisibility::Visible);
		FSlateBrush Brush;
		Brush.SetResourceObject(CurrentPair.Value);

		OverlayImage->SetBrush(Brush);
		
		if(AllItems.Num() == 1)
		{
			BTN_PrevItem->SetIsEnabled(false);
			BTN_NextItem->SetIsEnabled(false);
		}
	}
}

void UInventory::OnInventoryClose()
{
	BTN_PrevItem->SetIsEnabled(true);
	BTN_NextItem->SetIsEnabled(true);
}

void UInventory::ShowNextItem()
{
	if(AllItems.Num() == 0)
		return;
	
	index++;
	
	if(index > AllItems.Num()-1)
		index = 0;

	CurrentPair = AllItems[index];
		
	FText NewText = FText::FromString(CurrentPair.Key);
	TextBlockName->SetText(NewText);

	OverlayImage->SetVisibility(ESlateVisibility::Visible);
	FSlateBrush Brush;
	Brush.SetResourceObject(CurrentPair.Value); 
	OverlayImage->SetBrush(Brush);
}

void UInventory::ShowPrevItem()
{
	if(AllItems.Num() == 0)
		return;
	
	index--;
	
	if(index < 0)
		index = AllItems.Num()-1;

	CurrentPair = AllItems[index];
		
	FText NewText = FText::FromString(CurrentPair.Key);
	TextBlockName->SetText(NewText);
	
	OverlayImage->SetVisibility(ESlateVisibility::Visible);
	FSlateBrush Brush;
	Brush.SetResourceObject(CurrentPair.Value); 
	OverlayImage->SetBrush(Brush);
}