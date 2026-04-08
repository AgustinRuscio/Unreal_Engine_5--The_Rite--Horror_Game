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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemInspected, const FInventoryItemData&, ItemData);

class UButton;
class UTextBlock;
class UUniformGridPanel;

class UPickeableInventorySlot;
class UInventorySlotOptions;

UCLASS()
class THERITE_API UInventory : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnItemInspected OnItemInspected;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
//---------------- Inventory setter Methods
	bool CanRecieveItem() const;
	
	UPickeableInventorySlot* GetCurrentSlot() inline const { return CurrentSlot; }

//---------------- Actions Methods
	void SetSlotInfo(const FInventoryItemData& ClickedInfo, UPickeableInventorySlot* ClickedSlot);

	void SetMovingMode(bool NewState);
	void SetCombineMode(bool NewState);

	void PushItemToGrid(const FInventoryItemData& NewPickUpData);
	void RemoveItem(const FInventoryItemData& id);

	void ConfigSlotOptions(UPickeableInventorySlot* SelectedSlot);
	void ClearSlotOptions();

	void InspectItem(const FInventoryItemData& id);

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

	UPROPERTY(meta = (BindWidget))
	UInventorySlotOptions* WBP_InventorySlotOptions;

	UPROPERTY()
	TArray<UPickeableInventorySlot*> AllSlots;
	
	UPROPERTY()
	UPickeableInventorySlot* CurrentSlot;

	virtual bool Initialize() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void ClearDisplayedInfo();
};