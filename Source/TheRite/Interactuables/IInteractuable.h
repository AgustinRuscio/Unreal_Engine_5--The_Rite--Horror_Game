#pragma once

#include "CoreMinimal.h"
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
	 virtual USoundBase* GetSound() = 0;
};