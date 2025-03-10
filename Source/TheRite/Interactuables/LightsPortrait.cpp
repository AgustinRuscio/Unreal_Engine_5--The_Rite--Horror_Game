//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.1						//
//----------------------------------------------//

#include "LightsPortrait.h"
#include "TheRite/Widgets/LightsPuzzleWidget.h"
#include "TheRite/AlexPlayerController.h"
#include "CommonActivatableWidget.h"
#include "Components/SpotLightComponent.h"
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>

//----------------------------------------------------------------------------------------------------------------------
ALightsPortrait::ALightsPortrait()
{
 	PrimaryActorTick.bCanEverTick = true;

	Light = CreateDefaultSubobject<USpotLightComponent>("Light");
	Light->SetupAttachment(ObjectMesh);

	Button = CreateDefaultSubobject<UStaticMeshComponent>("Button up");
	Button->SetupAttachment(ObjectMesh);

	ButtonWidget = CreateDefaultSubobject<UWidgetComponent>("ButtonUI");
	ButtonWidget->SetupAttachment(Button);
}

//----------------------------------------------------------------------------------------------------------------------
bool ALightsPortrait::GetCurrentCorrectState() const
{
	return ColorIndex == -1 ? false : SwitcheableColors[ColorIndex] == CorrectColor;
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::Interaction()
{
	Super::Interaction();

	auto Controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->SetNewCursorVisibilityState(true);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::BeginPlay()
{
	Widget = Cast<ULightsPuzzleWidget>(ButtonWidget->GetClass());
	Widget->OnButtonPressed.AddDynamic(this, &ALightsPortrait::SwitchColor);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::SwitchColor()
{
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_Switch);
	ColorIndex++;

	if (ColorIndex >= SwitcheableColors.Num())
	{
		ColorIndex = 0;
	}

	Light->SetLightColor(SwitcheableColors[ColorIndex]);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::OnNoButtonPressed()
{

	auto Controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->SetNewCursorVisibilityState(false);

	LeaveFocus();

	OnLightChange.Broadcast();
}