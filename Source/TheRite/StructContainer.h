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

	FInventoryItemData()
	{
		DisplayImage = nullptr;
		ItemId = PickableItemsID::None;
		DisplayName = FText::FromString("Default Item");
		DisplayDescription = FText::FromString("Default Description");
	}

	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	class UTexture* DisplayImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	PickableItemsID ItemId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FText DisplayDescription;
};