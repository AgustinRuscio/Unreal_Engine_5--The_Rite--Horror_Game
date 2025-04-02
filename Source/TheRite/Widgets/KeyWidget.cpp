//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "KeyWidget.h"
#include "Components/TextBlock.h"


//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void UKeyWidget::SetKeyZoneText(FString newZone)
{
	ZoneText		  = *newZone;
	FString finalText = ZoneText + NotChangableText;

	TextComponent->SetText(FText::FromString(finalText));
}