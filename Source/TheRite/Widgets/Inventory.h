#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryChange, FString, itemName, UStaticMesh*, itemMesh);

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
	
	TArray<TPair<FString, UStaticMesh*>> AllItems;
	
	UPROPERTY(EditAnywhere)
	TMap<FString, UStaticMesh*> ItemsInIds;


	void AddItemToInventory(FString itemName, FString id);

	FOnInventoryChange OnInventoryChange;

	UFUNCTION(BlueprintCallable)
	void SetButtons(UButton* Next, UButton* Prev, UTextBlock* textBlock);

private:

	int8 index = 0;

	TPair<FString, UStaticMesh*> CurrentPair;
	
	
	UFUNCTION()
	void ShowNextItem();
	
	UFUNCTION()
	void ShowPrevItem();
};