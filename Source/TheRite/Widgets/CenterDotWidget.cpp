//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "CenterDotWidget.h"
#include "Components/Image.h"

//----------------------------------------------------------------------------------------------------------------------
void UCenterDotWidget::SetLockedDoorImage()
{
	NoneInteractionTexture->SetVisibility(ESlateVisibility::Hidden);
	InteractionTexture->SetVisibility(ESlateVisibility::Hidden);
	MainInteractionTexture->SetVisibility(ESlateVisibility::Hidden);
	CantInteractTexture->SetVisibility(ESlateVisibility::Hidden);
	LockedDoorTexture->SetVisibility(ESlateVisibility::Visible);
}

//----------------------------------------------------------------------------------------------------------------------
void UCenterDotWidget::SetCantInteractTexture()
{
	NoneInteractionTexture->SetVisibility(ESlateVisibility::Visible);
	InteractionTexture->SetVisibility(ESlateVisibility::Hidden);
	MainInteractionTexture->SetVisibility(ESlateVisibility::Hidden);
	CantInteractTexture->SetVisibility(ESlateVisibility::Visible);
	LockedDoorTexture->SetVisibility(ESlateVisibility::Hidden);
}

//----------------------------------------------------------------------------------------------------------------------
void UCenterDotWidget::SetNoneInteractionTexture()
{
	NoneInteractionTexture->SetVisibility(ESlateVisibility::Visible);
	InteractionTexture->SetVisibility(ESlateVisibility::Hidden);
	MainInteractionTexture->SetVisibility(ESlateVisibility::Hidden);
	CantInteractTexture->SetVisibility(ESlateVisibility::Hidden);
	LockedDoorTexture->SetVisibility(ESlateVisibility::Hidden);
}