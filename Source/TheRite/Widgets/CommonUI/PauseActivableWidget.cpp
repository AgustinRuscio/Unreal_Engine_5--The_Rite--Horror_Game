//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "PauseActivableWidget.h"
#include "TheRite/Characters/Alex.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include <Kismet/GameplayStatics.h>

void UPauseActivableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Player = Cast<AAlex>(UGameplayStatics::GetActorOfClass(this, AAlex::StaticClass()));
}

//----------------------------------------------------------------------------------------------------------------------
void UPauseActivableWidget::OnResume()
{
	Player->CallPauseFunc();
}

//----------------------------------------------------------------------------------------------------------------------
void UPauseActivableWidget::PushWidget(UCommonActivatableWidget* ActivatableWidgetClass)
{
	PauseStack->AddWidgetInstance(*ActivatableWidgetClass);
}

//----------------------------------------------------------------------------------------------------------------------
void UPauseActivableWidget::RemoveWidgetFromStack(UCommonActivatableWidget* WidgetToRemove)
{
	PauseStack->RemoveWidget(*WidgetToRemove);
}
