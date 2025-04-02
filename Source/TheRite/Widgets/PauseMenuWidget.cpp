//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "PauseMenuWidget.h"
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"

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