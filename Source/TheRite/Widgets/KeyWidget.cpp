#include "KeyWidget.h"

void UKeyWidget::SetKeyZoneText(FString newZone)
{
	ZoneText = *newZone;
	FString finalText = ZoneText + NotChangableText;
	TextComponent->SetText(FText::FromString(finalText));
}
