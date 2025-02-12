//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.3						//
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
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void OnResume();

	UFUNCTION(BlueprintCallable)
	void PushWidget(class UCommonActivatableWidget* ActivatableWidgetClass);

	UFUNCTION(BlueprintCallable)
	void RemoveWidgetFromStack(class UCommonActivatableWidget* WidgetToRemove);

public:
	UPROPERTY(BlueprintReadWrite)
	class UCommonActivatableWidgetStack* PauseStack;

	UPROPERTY(BlueprintAssignable)
	FOntogglePuaseOpen OnTogglePause;
	
private:
	class AAlex* Player;
};
