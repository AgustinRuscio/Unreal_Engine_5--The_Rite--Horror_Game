//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ChangingdWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

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