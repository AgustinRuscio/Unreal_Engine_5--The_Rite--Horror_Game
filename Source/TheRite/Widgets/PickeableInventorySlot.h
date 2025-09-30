//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "TheRite/StructContainer.h"
#include "PickeableInventorySlot.generated.h"

class UButton;
class UImage;

class UInventory;

UCLASS()
class THERITE_API UPickeableInventorySlot : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	bool GetIsOccupied() inline const { return bIsOccupied; }
	const FInventoryItemData& GetSlotDataInfo() inline const { return ItemInfo; }

	void SetUpInventory(UInventory* NewInventory);
	void SetIsBeingMoved(bool NewState);
	void SetCombining(bool NewState);

	void SetUpSlot(const FInventoryItemData& ItemData);
	void ClearSlot();

	void RemoveItemFromInventory();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bIsOccupied   = false;
	bool bIsBeingMoved = false;
	bool bisCombining  = false;

	FInventoryItemData ItemInfo;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonSlot;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;
	
	UPROPERTY(meta = (BindWidget))
	UImage* BorderImage;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	UTexture* EmptyImage;

	UPROPERTY()
	UInventory* Inventory;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual bool Initialize() override;

	UFUNCTION()
	void OnButtonPressed();

	void MovingLogic();
	void CombineLogic();
	void SelectingLogic();

	void SetImage(UTexture* DisplayImage) const;
	void SetOccupiedState(bool NewState);
};