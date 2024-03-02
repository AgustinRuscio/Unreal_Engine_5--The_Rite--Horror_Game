#include "ChangingdWidget.h"

void UChangingdWidget::SetKeyMode(bool isGamepad)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(isGamepad ? GamepadKeyImage : KeyboardKeyImage);

	DisplayImmage->SetBrush(Brush);
}
