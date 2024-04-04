//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"


void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	auto character = UGameplayStatics::GetActorOfClass(this, AAlex::StaticClass());
	Player = Cast<AAlex>(character);
}

void UPauseMenuWidget::OnResume()
{
	Player->CallPauseFunc();
}