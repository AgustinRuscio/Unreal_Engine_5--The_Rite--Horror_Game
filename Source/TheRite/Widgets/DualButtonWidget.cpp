//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.1						//
//----------------------------------------------//

#include "DualButtonWidget.h"

//----------------------------------------------------------------------------------------------------------------------
void UDualButtonWidget::YesButtonPressed()
{
	OnYesButtonPressed.Broadcast();
}

//----------------------------------------------------------------------------------------------------------------------
void UDualButtonWidget::NoButtonPressed()
{
	OnNoButtonPressed.Broadcast();
}