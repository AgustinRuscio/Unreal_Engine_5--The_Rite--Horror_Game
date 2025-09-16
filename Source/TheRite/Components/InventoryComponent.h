//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TheRite/StructContainer.h"
#include "TheRite/EnumsContainer.h"
#include "InventoryComponent.generated.h"

class UInventory;
class UPickeableInventorySlot;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERITE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	void ToggleInventory(bool visible);

	void AddItem(const FInventoryItemData& ItemData);

	void RemoveItem(PickableItemsID ItemData);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<UPickeableInventorySlot> InventorySlotWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<UInventory> InventoryWidgetClass;

	UPROPERTY()
	UInventory* PlayerInventory;

	TArray<TTuple<UPickeableInventorySlot*, int, int, PickableItemsID>> SlotsContainer;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	void CreateInventoryWidget();
	
};