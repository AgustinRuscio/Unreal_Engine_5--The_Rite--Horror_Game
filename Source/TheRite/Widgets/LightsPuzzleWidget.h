//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LightsPuzzleWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUiButtonPressed);

UCLASS()
class THERITE_API ULightsPuzzleWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintCallable)
	FOnUiButtonPressed OnButtonPressed;
};