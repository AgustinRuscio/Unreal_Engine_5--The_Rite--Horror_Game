//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "TheRite/EnumsContainer.h"
#include "TheRite/StructContainer.h"
#include "UObject/Interface.h"
#include "IInteractuable.generated.h"

UINTERFACE(MinimalAPI)
class UIInteractuable : public UInterface
{
	GENERATED_BODY()
};

class THERITE_API IIInteractuable
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	virtual void Interaction() = 0;
	virtual bool IsPickable() const = 0;
	virtual bool IsMainItem() const = 0;
	virtual bool GetCanInteract() const = 0;
	virtual bool IsRemovable() const = 0;

	virtual FString GetItemName() const = 0;
	virtual FString GetItemDescription() const = 0;
	virtual PickableItemsID GetItemID() const = 0;
	virtual USoundBase* GetSound() const = 0;
	virtual FInventoryItemData GetItemInventoryData() const = 0;
	virtual TTuple<bool, FString, PickableItemsID> CheckRemove() const = 0;
	
	virtual void Deactivate() = 0;
	virtual void Activate() = 0;
};