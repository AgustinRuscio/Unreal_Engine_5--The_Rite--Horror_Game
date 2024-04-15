//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ChangingdWidget.h"

void UChangingdWidget::SetKeyMode(bool isGamepad)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(isGamepad ? GamepadKeyImage : KeyboardKeyImage);

	DisplayImmage->SetBrush(Brush);
}

void UChangingdWidget::SetChangingText(FText newText)
{
	ChangingText->SetText(newText);
}