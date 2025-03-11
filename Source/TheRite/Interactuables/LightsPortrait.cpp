//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.1						//
//----------------------------------------------//

#include "LightsPortrait.h"
#include "PressableButton.h"
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

	LightSourceMesh = CreateDefaultSubobject<UStaticMeshComponent>("Light source");
	LightSourceMesh->SetupAttachment(ObjectMesh);
}

//----------------------------------------------------------------------------------------------------------------------
bool ALightsPortrait::GetCurrentCorrectState() const
{
	return ColorIndex == -1 ? false : SwitcheableColors[ColorIndex] == CorrectColor;
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::BeginPlay()
{
	Super::BeginPlay();

	PortraitButton->OnInteractionTrigger.AddDynamic(this, &ALightsPortrait::SwitchColor);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::SwitchColor(AInteractor* interactor)
{
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_Switch);
	ColorIndex++;

	if (ColorIndex >= SwitcheableColors.Num())
	{
		ColorIndex = 0;
	}

	Light->SetLightColor(SwitcheableColors[ColorIndex]);

	OnLightChange.Broadcast();
}