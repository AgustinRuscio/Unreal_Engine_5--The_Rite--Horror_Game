#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TheRite/EnumsContainer.h"
#include "Materials/MaterialInterface.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Inventory.generated.h"


UCLASS()
class THERITE_API UInventory : public UUserWidget
{
	GENERATED_BODY()

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


	void AddItemToInventory(FString itemName, PickableItemsID id);

	UFUNCTION(BlueprintCallable)
	void SetWidgetsObject(UButton* Next, UButton* Prev, UTextBlock* textBlock, UImage* imageToDisplay);
	
	void OnInventoryOpen();
	
	void OnInventoryClose();
	
	UFUNCTION()
	void ShowNextItem();
	
	UFUNCTION()
	void ShowPrevItem();

	void RemoveItem(FString itemName, PickableItemsID id);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:

	int8 index = 0;

	TPair<FString, UMaterialInterface*> CurrentPair;
};