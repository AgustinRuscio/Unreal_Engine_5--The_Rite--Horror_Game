//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "CenterDotWidget.h"
#include "Components/Image.h"

void UCenterDotWidget::Interact(bool Visible, bool LockedDoor, bool Wait, bool MainItem)
{
	if(LockedDoor)
		SetLockedDoorImage();
	else
	{
		if(Wait)
			SetWaitImage();
		else
		{
			if(Visible)
				SetVisibleImage();
			else
			{
				if(MainItem)
					SetMainObjectImage();
				else
					SetDefaultImage();
			}
		}
	}
}

void UCenterDotWidget::SetLockedDoorImage()
{
	CompleteCircle->SetVisibility(ESlateVisibility::Hidden);
	InteractCircle->SetVisibility(ESlateVisibility::Hidden);
	MainInteractCircle->SetVisibility(ESlateVisibility::Hidden);
	Talking->SetVisibility(ESlateVisibility::Hidden);
	ClosedDoor->SetVisibility(ESlateVisibility::Visible);
}

void UCenterDotWidget::SetWaitImage()
{
	CompleteCircle->SetVisibility(ESlateVisibility::Visible);
	InteractCircle->SetVisibility(ESlateVisibility::Hidden);
	MainInteractCircle->SetVisibility(ESlateVisibility::Hidden);
	Talking->SetVisibility(ESlateVisibility::Visible);
	ClosedDoor->SetVisibility(ESlateVisibility::Hidden);
}

void UCenterDotWidget::SetVisibleImage()
{
	CompleteCircle->SetVisibility(ESlateVisibility::Visible);
	InteractCircle->SetVisibility(ESlateVisibility::Hidden);
	MainInteractCircle->SetVisibility(ESlateVisibility::Hidden);
	Talking->SetVisibility(ESlateVisibility::Hidden);
	ClosedDoor->SetVisibility(ESlateVisibility::Hidden);
}

void UCenterDotWidget::SetMainObjectImage()
{
	CompleteCircle->SetVisibility(ESlateVisibility::Hidden);
	InteractCircle->SetVisibility(ESlateVisibility::Hidden);
	MainInteractCircle->SetVisibility(ESlateVisibility::Visible);
	Talking->SetVisibility(ESlateVisibility::Hidden);
	ClosedDoor->SetVisibility(ESlateVisibility::Hidden);
}

void UCenterDotWidget::SetDefaultImage()
{
	CompleteCircle->SetVisibility(ESlateVisibility::Hidden);
	InteractCircle->SetVisibility(ESlateVisibility::Visible);
	MainInteractCircle->SetVisibility(ESlateVisibility::Hidden);
	Talking->SetVisibility(ESlateVisibility::Hidden);
	ClosedDoor->SetVisibility(ESlateVisibility::Hidden);
}
