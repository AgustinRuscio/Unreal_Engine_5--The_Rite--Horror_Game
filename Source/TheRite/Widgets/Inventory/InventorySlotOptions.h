//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InventorySlotOptions.generated.h"

class UButton;

class UPickeableInventorySlot;
class UInventory;

UCLASS()
class THERITE_API UInventorySlotOptions : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void SetUpInventory(UInventory* InventoryToUse);

	void OpenOptions(UPickeableInventorySlot* ClickedButton);
	void CloseOptions();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Inspect;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Move;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Combine;
		
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Remove;

	UPROPERTY()
	UPickeableInventorySlot* CurrentSlot;

	UPROPERTY()
	UInventory* Inventory;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual bool Initialize() override;

	UFUNCTION()
	void OnInspectButtonClicked();

	UFUNCTION()
	void OnMoveButtonClicked();

	UFUNCTION()
	void OnCombineButtonClicked();

	UFUNCTION()
	void OnRemoveButtonClicked();
};