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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInspecItem, bool, state);

class AInspectItem;
class UInventory;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERITE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	FOnInspecItem OnInspectItem;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	bool DoesInvetoryHasSpace() inline const;
	void ToggleInventory(bool visible);

	void AddItem(const FInventoryItemData& ItemData);

	void RemoveItem(const FInventoryItemData& ItemData);

	UFUNCTION()
	void InspectItem(const FInventoryItemData& itemData);

	UFUNCTION()
	void LeaveInspection();

	UFUNCTION()
	void MoveInspetedItem(FVector2D vector);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	int InventoryZOrder;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float InspectSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<AInspectItem> InspecItemClass;

	
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<UUserWidget> InspectWidgetClass;

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