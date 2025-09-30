//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheRite/StructContainer.h"
#include "InvenotryOnlyItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemAddedToInvenotry);

UCLASS()
class THERITE_API AInvenotryOnlyItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AInvenotryOnlyItem();

	FOnItemAddedToInvenotry OnItemAddedToInventory;

	const FInventoryItemData& GetSlotDataInfo() inline const { return ItemInfo; }


private:
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	FInventoryItemData ItemInfo;
	virtual void BeginPlay() override;
};