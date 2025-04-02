//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PauseActivableWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOntogglePuaseOpen, bool, Active);

UCLASS()
class THERITE_API UPauseActivableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
		

public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(BlueprintReadWrite)
	class UCommonActivatableWidgetStack* PauseStack;

	UPROPERTY(BlueprintAssignable)
	FOntogglePuaseOpen OnTogglePause;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void OnResume();

	UFUNCTION(BlueprintCallable)
	void PushWidget(class UCommonActivatableWidget* ActivatableWidgetClass);

	UFUNCTION(BlueprintCallable)
	void RemoveWidgetFromStack(class UCommonActivatableWidget* WidgetToRemove);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	class AAlex* Player;
};