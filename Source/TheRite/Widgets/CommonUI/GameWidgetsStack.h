//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
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
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	UCommonActivatableWidget* PushWidgetToScreen(TSubclassOf <class UCommonActivatableWidget> WidgetClass);

	virtual UCommonActivatableWidget* PushWidgetToScreen_Implementation(TSubclassOf <class UCommonActivatableWidget> WidgetClass);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveWidgetFromScreen(class UCommonActivatableWidget* WidgetPointer);
};