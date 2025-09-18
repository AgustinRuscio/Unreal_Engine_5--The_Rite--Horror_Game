//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "TheRite/EnumsContainer.h"
#include "TheRite/StructContainer.h"
#include "Inventory.generated.h"

class UButton;
class UTextBlock;
class UUniformGridPanel;

class UPickeableInventorySlot;

UCLASS()
class THERITE_API UInventory : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
//---------------- Inventory setter Methods
	bool CanRecieveItem() const;
		
//---------------- Actions Methods
	void SetSlotInfo(const FInventoryItemData& ClickedInfo, UPickeableInventorySlot* ClickedSlot);
	void ClearDisplayedInfo();

	void PushItemToGrid(const FInventoryItemData& NewPickUpData);
	void RemoveItem(const PickableItemsID& id);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* SlotsPanel;

	UPROPERTY()
	TArray<UPickeableInventorySlot*> AllSlots;
	
	UPROPERTY()
	UPickeableInventorySlot* CurrentSlot;

	virtual void NativeConstruct() override;
};