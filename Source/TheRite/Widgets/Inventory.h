//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "TheRite/EnumsContainer.h"
#include "Inventory.generated.h"

class UButton;
class UTextBlock;
class UMaterialInterface;
class UImage;


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

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* TextBlockName;

	UPROPERTY(BlueprintReadWrite)
	UImage* OverlayImage;
	
	TArray<TPair<FString, UMaterialInterface*>> AllItems;
	
	UPROPERTY(EditAnywhere)
	TMap<PickableItemsID, UMaterialInterface*> ItemsInIds;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
//---------------- Inventory setter Methods
	UFUNCTION(BlueprintCallable)
	void SetWidgetsObject(UButton* Next, UButton* Prev, UTextBlock* textBlock, UImage* imageToDisplay);

	void AddItemToInventory(FString itemName, PickableItemsID id);
	void RemoveItem(FString itemName, PickableItemsID id);
	
//---------------- Actions Methods
	void OnInventoryOpen();
	
	void OnInventoryClose();
	
	UFUNCTION()
	void ShowNextItem();
	
	UFUNCTION()
	void ShowPrevItem();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	int8 index = 0;

	TPair<FString, UMaterialInterface*> CurrentPair;
};