//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TheRite/EnumsContainer.h"
#include "TheRite/StructContainer.h"
#include "InventoryComponent.generated.h"

class UInventory;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERITE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	bool DoesInvetoryHasSpace() inline const;
	void ToggleInventory(bool visible);

	void AddItem(const FInventoryItemData& ItemData);

	void RemoveItem(const FInventoryItemData& ItemData);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	int InventoryZOrder;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<UInventory> InventoryWidgetClass;

	UPROPERTY()
	UInventory* PlayerInventory;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	void CreateInventoryWidget();
};