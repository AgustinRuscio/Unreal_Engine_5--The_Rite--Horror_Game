//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ChangingdWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void UChangingdWidget::SetKeyMode(bool isGamepad)
{
	isGamepad ? SetGamepadImages() : SetKeyboardImages();
	
	Index = 0;
}

//----------------------------------------------------------------------------------------------------------------------
void UChangingdWidget::SetChangingText(FText newText)
{
	ChangingText->SetText(newText);
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void UChangingdWidget::SetGamepadImages()
{
	for (auto Element : DisplayImmages)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(GamepadKeyImage[Index]);
		Element->SetBrush(Brush);
		++Index;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UChangingdWidget::SetKeyboardImages()
{
	for (auto Element : DisplayImmages)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(KeyboardKeyImage[Index]);
		Element->SetBrush(Brush);
		++Index;
	}
}