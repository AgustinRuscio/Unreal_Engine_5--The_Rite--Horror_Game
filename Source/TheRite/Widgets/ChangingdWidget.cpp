//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ChangingdWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include <TheRite/AlexPlayerController.h>

//*****************************Public*********************************************
//********************************************************************************

float UChangingdWidget::GetHideTime() const
{
	return DeactivateTime;
}

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
void UChangingdWidget::SelfRemove()
{
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());

	if (controller)
		controller->RemoveWidget(this);
}

//----------------------------------------------------------------------------------------------------------------------
void UChangingdWidget::NativeOnActivated() 
{
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());

	if (controller)
	{
		SetKeyMode(controller->GetIsUsingGamepad());

		if (!controller->OnKeyPressed.IsBound())
			controller->OnKeyPressed.AddDynamic(this, &UChangingdWidget::SetKeyMode);
	}

	if (bAutoDisable)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(Timer_ClockClue))
		{
			GetWorld()->GetTimerManager().SetTimer(Timer_ClockClue, this, &UChangingdWidget::AutoHide, DeactivateTime, false);
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(Timer_ClockClue);
			GetWorld()->GetTimerManager().SetTimer(Timer_ClockClue, this, &UChangingdWidget::AutoHide, DeactivateTime, false);
		}
	}
}

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

void UChangingdWidget::AutoHide()
{
	Timer_ClockClue.Invalidate();
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());

	if (controller) {
		controller->OnKeyPressed.RemoveDynamic(this, &UChangingdWidget::SetKeyMode);
		controller->RemoveWidget(this);

	}
}