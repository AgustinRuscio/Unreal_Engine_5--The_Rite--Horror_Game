//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "CenterDotWidget.h"

void UCenterDotWidget::Interact(bool Visible, bool LockedDoor, bool Wait, bool MainItem)
{
	if(LockedDoor)
	{
		CompleteCircle->SetVisibility(ESlateVisibility::Hidden);
		InteractCircle->SetVisibility(ESlateVisibility::Hidden);
		MainInteractCircle->SetVisibility(ESlateVisibility::Hidden);
		Talking->SetVisibility(ESlateVisibility::Hidden);
		ClosedDoor->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		if(Wait)
		{
			CompleteCircle->SetVisibility(ESlateVisibility::Visible);
			InteractCircle->SetVisibility(ESlateVisibility::Hidden);
			MainInteractCircle->SetVisibility(ESlateVisibility::Hidden);
			Talking->SetVisibility(ESlateVisibility::Visible);
			ClosedDoor->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			if(Visible)
			{
				CompleteCircle->SetVisibility(ESlateVisibility::Visible);
				InteractCircle->SetVisibility(ESlateVisibility::Hidden);
				MainInteractCircle->SetVisibility(ESlateVisibility::Hidden);
				Talking->SetVisibility(ESlateVisibility::Hidden);
				ClosedDoor->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				if(MainItem)
				{
					CompleteCircle->SetVisibility(ESlateVisibility::Hidden);
					InteractCircle->SetVisibility(ESlateVisibility::Hidden);
					MainInteractCircle->SetVisibility(ESlateVisibility::Visible);
					Talking->SetVisibility(ESlateVisibility::Hidden);
					ClosedDoor->SetVisibility(ESlateVisibility::Hidden);
				}
				else
				{
					CompleteCircle->SetVisibility(ESlateVisibility::Hidden);
					InteractCircle->SetVisibility(ESlateVisibility::Visible);
					MainInteractCircle->SetVisibility(ESlateVisibility::Hidden);
					Talking->SetVisibility(ESlateVisibility::Hidden);
					ClosedDoor->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		}
	}
}
