//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "Inventory.h"
#include "Components/TextBlock.h"
#include "Materials/MaterialInterface.h"
#include "TheRite/Widgets/PickeableInventorySlot.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"


//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
#pragma region Inventory setter Methods
bool UInventory::CanRecieveItem()
{
	return CurrentRow < RowAmmount && CurrentColum < ColumAmmount;
}

int UInventory::GetRowIndex(UPickeableInventorySlot* a) const
{
	for (const auto& SlotTuple : SlotsContainer)
	{
		if (SlotTuple.Get<0>() == a)
		{
			return SlotTuple.Get<1>();
		}
	}

	return -1;
}

//----------------------------------------------------------------------------------------------------------------------
int UInventory::GetColumnIndex(UPickeableInventorySlot* a) const
{
	for (const auto& SlotTuple : SlotsContainer)
	{
		if (SlotTuple.Get<0>() == a)
		{
			return SlotTuple.Get<2>();
		}
	}

	return -1;
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::SetWidgetsObject(UButton* Next, UButton* Prev, UImage* imageToDisplay)
{
	BTN_NextItem = Next;
	BTN_PrevItem = Prev;
	OverlayImage = imageToDisplay;
	
	BTN_NextItem->OnClicked.AddDynamic(this, &UInventory::ShowNextItem);
	BTN_PrevItem->OnClicked.AddDynamic(this, &UInventory::ShowPrevItem);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::AddItemToInventory(FString itemName, FString Description, PickableItemsID id)
{
	for (auto Element : AllItems)
	{
		if(Element.Key == itemName)
			return;
	}
	
	TPair<FString, UMaterialInterface*> addedPair;
	
	addedPair.Key = itemName;
	addedPair.Value = ItemsInIds[id];

	TPair<FString, FString> addedPairTwo;
	addedPairTwo.Key = itemName;
	addedPairTwo.Value = Description;
	
	AllItems.Add(addedPair);
	AllDescriptions.Add(addedPairTwo);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::RemoveItem(FString itemName, PickableItemsID id)
{
	for (auto Element : AllItems)
	{
		if(Element.Key == itemName)
		{
			TPair<FString, UMaterialInterface*> removedPair;

			removedPair.Key = itemName;
			removedPair.Value = ItemsInIds[id];

			TPair<FString, FString> addedPairTwo;

			for (auto Pair : AllDescriptions)
			{
				if (Pair.Key == itemName)
				{
					addedPairTwo = Pair;
					break;
				}
			}

			AllItems.Remove(removedPair);
			AllDescriptions.Remove(addedPairTwo);
			return;
		}
	}
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region Actions Methods
void UInventory::OnInventoryOpen()
{
	if(AllItems.Num() == 0)
	{
		FText NewText = FText::FromString(TEXT("Empty"));
		ItemName->SetText(NewText);


		FText NewDescription = FText::FromString(TEXT(""));
		ItemDescription->SetText(NewDescription);

		OverlayImage->SetVisibility(ESlateVisibility::Hidden);
		
		BTN_PrevItem->SetIsEnabled(false);
		BTN_NextItem->SetIsEnabled(false);
	}
	else
	{
		CurrentPair = AllItems[index];
		
		FText NewText = FText::FromString(CurrentPair.Key);
		ItemName->SetText(NewText);


		CurrentPairDescription = AllDescriptions[index];

		OverlayImage->SetVisibility(ESlateVisibility::Visible);
		FText NewDescription = FText::FromString(CurrentPairDescription.Value);
		ItemDescription->SetText(NewDescription);


		OverlayImage->SetVisibility(ESlateVisibility::Visible);
		FSlateBrush Brush;
		UE::Slate::FDeprecateVector2DParameter v(1000.f, 1000.f);
		Brush.SetImageSize(v);
		Brush.SetResourceObject(CurrentPair.Value);

		OverlayImage->SetBrush(Brush);
		
		if(AllItems.Num() == 1)
		{
			BTN_PrevItem->SetIsEnabled(false);
			BTN_NextItem->SetIsEnabled(false);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::OnInventoryClose()
{
	BTN_PrevItem->SetIsEnabled(true);
	BTN_NextItem->SetIsEnabled(true);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::ShowNextItem()
{
	if(AllItems.Num() == 0)
		return;
	
	index++;
	
	if(index > AllItems.Num()-1)
		index = 0;

	CurrentPair = AllItems[index];
	CurrentPairDescription = AllDescriptions[index];
		
	FText NewText = FText::FromString(CurrentPair.Key);
	ItemName->SetText(NewText);

	FText NewTextDescription = FText::FromString(CurrentPairDescription.Value);
	ItemDescription->SetText(NewTextDescription);

	OverlayImage->SetVisibility(ESlateVisibility::Visible);
	OverlayImage->SetVisibility(ESlateVisibility::Visible);
	FSlateBrush Brush;
	UE::Slate::FDeprecateVector2DParameter v(1000.f, 1000.f);
	Brush.SetImageSize(v);
	Brush.SetResourceObject(CurrentPair.Value);
	OverlayImage->SetBrush(Brush);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::ShowPrevItem()
{
	if(AllItems.Num() == 0)
		return;
	
	index--;
	
	if(index < 0)
		index = AllItems.Num()-1;

	CurrentPair = AllItems[index];
	CurrentPairDescription = AllDescriptions[index];
		
	FText NewText = FText::FromString(CurrentPair.Key);
	ItemName->SetText(NewText);
	
	FText NewTextDescription = FText::FromString(CurrentPairDescription.Value);
	ItemDescription->SetText(NewTextDescription);

	OverlayImage->SetVisibility(ESlateVisibility::Visible);
	FSlateBrush Brush;
	Brush.SetResourceObject(CurrentPair.Value); 

	UE::Slate::FDeprecateVector2DParameter v (1000.f, 1000.f);
	Brush.SetImageSize(v);

	OverlayImage->SetBrush(Brush);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::SetInfo(FInventoryItemData ClickedInfo)
{
	ItemName->SetText(ClickedInfo.DisplayName);
	ItemDescription->SetText(ClickedInfo.DisplayDescription);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::PushItemToGrid(UPickeableInventorySlot* NewPickUp)
{
	for (int row = 0; row < RowAmmount; row++)
	{
		for (int col = 0; col < ColumAmmount; col++)
		{
			bool bOccupied = false;
			for (auto& SlotTuple : SlotsContainer)
			{
				if (SlotTuple.Get<1>() == row && SlotTuple.Get<2>() == col)
				{
					bOccupied = true;
					break;
				}
			}

			if (!bOccupied)
			{
				SlotsPanel->AddChildToUniformGrid(NewPickUp, row, col);

				TTuple<UPickeableInventorySlot*, int, int> NewSlot(NewPickUp, row, col);
				SlotsContainer.Add(NewSlot);

				return;
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::RemoveItem(UPickeableInventorySlot* NewPickUp)
{
	for (int i = 0; i < SlotsContainer.Num(); i++)
	{
		if (SlotsContainer[i].Get<0>() == NewPickUp)
		{
			// Quitar el widget de la UI
			if (NewPickUp)
			{
				NewPickUp->RemoveFromParent();
			}

			// Eliminar la tupla del array para liberar el slot
			SlotsContainer.RemoveAt(i);
			return;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UInventory::NativeConstruct()
{
	
}


#pragma endregion