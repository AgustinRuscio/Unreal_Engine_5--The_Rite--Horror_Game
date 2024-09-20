//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "CenterDotWidget.h"
#include "Components/Image.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
//void UCenterDotWidget::Interact(bool InteractionDisable, bool LockedDoor, bool PlayerTalking, bool IsMainItem)
//{
//	if(LockedDoor)
//		SetLockedDoorImage();
//	else
//	{
//		if(PlayerTalking)
//			SetCantInteractTexture();
//		else
//		{
//			if(InteractionDisable)
//				SetNoneInteractionTexture();
//			else
//			{
//				if(IsMainItem)
//					SetMainInteractionTexture();
//				else
//					SetInteractionTexture();
//			}
//		}
//	}
//}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
#pragma region Setter Methods
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

//----------------------------------------------------------------------------------------------------------------------
//void UCenterDotWidget::SetMainInteractionTexture()
//{
//	NoneInteractionTexture->SetVisibility(ESlateVisibility::Hidden);
//	InteractionTexture->SetVisibility(ESlateVisibility::Hidden);
//	MainInteractionTexture->SetVisibility(ESlateVisibility::Visible);
//	CantInteractTexture->SetVisibility(ESlateVisibility::Hidden);
//	LockedDoorTexture->SetVisibility(ESlateVisibility::Hidden);
//}
//
////----------------------------------------------------------------------------------------------------------------------
//void UCenterDotWidget::SetInteractionTexture()
//{
//	NoneInteractionTexture->SetVisibility(ESlateVisibility::Hidden);
//	InteractionTexture->SetVisibility(ESlateVisibility::Visible);
//	MainInteractionTexture->SetVisibility(ESlateVisibility::Hidden);
//	CantInteractTexture->SetVisibility(ESlateVisibility::Hidden);
//	LockedDoorTexture->SetVisibility(ESlateVisibility::Hidden);
//}
#pragma endregion