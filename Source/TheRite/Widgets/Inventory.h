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
class UMaterialInterface;
class UImage;
class UUniformGridPanel;
class UPickeableInventorySlot;

UCLASS()
class THERITE_API UInventory : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(BlueprintReadWrite)
	FString ObjectText;
	
	UPROPERTY(BlueprintReadWrite)
	UButton* BTN_NextItem;
	
	UPROPERTY(BlueprintReadWrite)
	UButton* BTN_PrevItem;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* SlotsPanel;

	UPROPERTY(BlueprintReadWrite)
	UImage* OverlayImage;
	
	TArray<TPair<FString, UMaterialInterface*>> AllItems;
	TArray<TPair<FString, FString>> AllDescriptions;
	
	UPROPERTY(EditAnywhere)
	TMap<PickableItemsID, UMaterialInterface*> ItemsInIds;

	TArray<UPickeableInventorySlot*> AllSlots;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
//---------------- Inventory setter Methods
	bool CanRecieveItem();
	
	int GetRowIndex(UPickeableInventorySlot* a) const;
	int GetColumnIndex(UPickeableInventorySlot* a) const;

	UFUNCTION(BlueprintCallable)
	void SetWidgetsObject(UButton* Next, UButton* Prev, UImage* imageToDisplay);

	void AddItemToInventory(FString itemName, FString Description, PickableItemsID id);
	void RemoveItem(FString itemName, PickableItemsID id);
	
//---------------- Actions Methods
	void OnInventoryOpen();
	
	void OnInventoryClose();
	
	UFUNCTION()
	void ShowNextItem();
	
	UFUNCTION()
	void ShowPrevItem();

	void SetSlotInfo(FInventoryItemData ClickedInfo, UPickeableInventorySlot* CurrentSlotClicked);
	void ClearSlot();

	void PushItemToGrid(const FInventoryItemData& NewPickUp);
	void RemoveItem(PickableItemsID id);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	int8 index = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Customization")
	int8 RowAmmount = 3;
	UPROPERTY(EditDefaultsOnly, Category = "Customization")
	int8 ColumAmmount = 3;

	int8 CurrentRow = -1;
	int8 CurrentColum = -1;

	TPair<FString, UMaterialInterface*> CurrentPair;
	TPair<FString, FString> CurrentPairDescription;

	TArray<TTuple<UPickeableInventorySlot*, int, int>> SlotsContainer;

	UPROPERTY()
	UPickeableInventorySlot* CurrentSlot;

	virtual void NativeConstruct() override;
};