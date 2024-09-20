//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "PauseMenuWidget.h"
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Player = Cast<AAlex>( UGameplayStatics::GetActorOfClass(this, AAlex::StaticClass()));
}

//----------------------------------------------------------------------------------------------------------------------
void UPauseMenuWidget::OnResume()
	{
	Player->CallPauseFunc();
}