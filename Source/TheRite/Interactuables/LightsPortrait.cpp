//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.1						//
//----------------------------------------------//

#include "LightsPortrait.h"
#include "TheRite/Widgets/DualButtonWidget.h"
#include "TheRite/AlexPlayerController.h"
#include "Components/SpotLightComponent.h"
#include <Kismet/GameplayStatics.h>

//----------------------------------------------------------------------------------------------------------------------
ALightsPortrait::ALightsPortrait()
{
 	PrimaryActorTick.bCanEverTick = true;

	Light = CreateDefaultSubobject<USpotLightComponent>("Light");
	Light->SetupAttachment(ObjectMesh);
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
	Super::BeginPlay();
	
	Widget = Cast<UDualButtonWidget>(DisplatedWidget);

	Widget->OnYesButtonPressed.AddDynamic(this, &ALightsPortrait::OnYesButtonPressed);
	Widget->OnNoButtonPressed.AddDynamic(this, &ALightsPortrait::OnNoButtonPressed);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::OnYesButtonPressed()
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