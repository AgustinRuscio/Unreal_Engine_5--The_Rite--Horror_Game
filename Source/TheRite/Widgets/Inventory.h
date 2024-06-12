//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheRite/EnumsContainer.h"
#include "Inventory.generated.h"

class UButton;
class UTextBlock;
class UMaterialInterface;
class UImage;


UCLASS()
class THERITE_API UInventory : public UUserWidget
{
	GENERATED_BODY()

public:
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

	
public:
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

private:
	int8 index = 0;

	TPair<FString, UMaterialInterface*> CurrentPair;
};