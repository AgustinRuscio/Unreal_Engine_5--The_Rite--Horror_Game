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
	bool GetIsOccupied() inline const {return bIsOccupied; }
	FInventoryItemData GetSlotDataInfo() inline const { return ItemInfo; }

	void SetUpInventory(UInventory* NewInventory);

	void SetUpSlot(FInventoryItemData ItemData);
	void ClearSlot();

private:
	bool bIsOccupied = false;

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

	virtual bool Initialize() override;

	UFUNCTION()
	void OnButtonPressed();

	void SetImage(UTexture* DisplayImage);

};