//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "DualButtonWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FYesButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoButtonPressed);

UCLASS()
class THERITE_API UDualButtonWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FYesButtonPressed OnYesButtonPressed;
	FNoButtonPressed OnNoButtonPressed;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	UFUNCTION(BlueprintCallable)
	virtual void YesButtonPressed();

	UFUNCTION(BlueprintCallable)
	virtual void NoButtonPressed();
};