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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", Meta = (ExposeOnSpawn = "true"))
	int Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", Meta = (ExposeOnSpawn = "true"))
	int Column;

	void SetUpInventory(UInventory* NewInventory);
	void SetUpSlot(FInventoryItemData ItemData);


private:
	bool bIsOccupied = false;

	FInventoryItemData ItemInfo;
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonSlot;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY()
	UInventory* Inventory;

	virtual bool Initialize() override;


	UFUNCTION()
	void OnButtonPressed();
};