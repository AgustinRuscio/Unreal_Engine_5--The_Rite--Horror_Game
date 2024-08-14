//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "TheRite/EnumsContainer.h"
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
	virtual void Interaction() = 0;
	virtual bool IsPickable() const = 0;
	virtual bool IsMainItem() const = 0;
	virtual bool GetCanInteract() const = 0;
	virtual bool IsRemovable() const = 0;

	virtual FString GetItemName() const = 0;
	virtual PickableItemsID GetItemID() const = 0;
	virtual USoundBase* GetSound() const = 0;
	virtual TTuple<bool, FString, PickableItemsID> CheckRemove() const = 0;
	
	virtual void SetPickeableSettings(bool isPickeable, FString nameToDisplay, PickableItemsID id) = 0;

	virtual void Deactivate() = 0;
	virtual void Activate() = 0;
};