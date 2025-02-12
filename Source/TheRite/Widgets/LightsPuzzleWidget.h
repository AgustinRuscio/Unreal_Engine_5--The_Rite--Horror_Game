//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "TheRite/Widgets/DualButtonWidget.h"
#include "LightsPuzzleWidget.generated.h"

UCLASS()
class THERITE_API ULightsPuzzleWidget : public UDualButtonWidget
{
	GENERATED_BODY()
	
public:
	virtual void YesButtonPressed() override;

	virtual void NoButtonPressed() override;
};