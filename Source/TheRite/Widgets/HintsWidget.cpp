//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "HintsWidget.h"
#include "Components/Image.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------

void UHintsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	JoystickChecker();
	TimerChecker(InDeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void UHintsWidget::MakeVisible()
{
	this->SetVisibility(ESlateVisibility::Visible);
	bIsOn = true;
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void UHintsWidget::JoystickChecker()
{
	KeyImage->SetBrushFromTexture(bJoystick ? SquareTexture : MTexture);
}

//----------------------------------------------------------------------------------------------------------------------
void UHintsWidget::TimerChecker(float deltaTime)
{
	if(!bIsOn)
		this->SetVisibility(ESlateVisibility::Hidden);
	else
	{
		Timer += deltaTime;

		if(Timer < TimerCD) return;

		bIsOn = false;
		Timer = 0.0f;
	}
}