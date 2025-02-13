//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.3						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameWidgetsStack.generated.h"


UCLASS()
class THERITE_API UGameWidgetsStack : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	
	UFUNCTION(BlueprintImplementableEvent)
	void PushWidgetToScreen(TSubclassOf <class UCommonActivatableWidget> WidgetClass);

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveWidgetFromScreen(class UCommonActivatableWidget* WidgetPointer);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//

};