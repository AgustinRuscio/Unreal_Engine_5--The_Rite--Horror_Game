//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "KeyWidget.h"
#include "Components/TextBlock.h"


//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void UKeyWidget::SetKeyZoneText(FString newZone)
{
	ZoneText = *newZone;
	FString finalText = ZoneText + NotChangableText;
	TextComponent->SetText(FText::FromString(finalText));
}