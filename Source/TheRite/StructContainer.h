//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "EnumsContainer.h"
#include "StructContainer.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItemData
{
public: 
	GENERATED_BODY()

	FInventoryItemData()
	{
		bIsRemovable = false;
		DisplayName = FText::FromString("Default Item");
		DisplayDescription = FText::FromString("Default Description");
		ItemId = PickableItemsID::None;
		DisplayImage = nullptr;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	bool bIsRemovable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FText DisplayDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	PickableItemsID ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	class UTexture* DisplayImage;
};