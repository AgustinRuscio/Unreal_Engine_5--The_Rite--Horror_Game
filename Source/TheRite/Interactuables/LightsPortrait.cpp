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

void ALightsPortrait::Interaction()
{
Super::Interaction();
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::BeginPlay()
{
	Super::BeginPlay();

	originalLocation = Button->GetRelativeLocation();
	endLocation = originalLocation + LocationToAdd;


	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("ButtonPressedTick"));
	ButtonTimeLine.AddInterpFloat(ButtonPressedCurveFloat, CameraTargetTick);

	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("ButtonPressedFinished"));
	ButtonTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);


	auto widget = ButtonWidget->GetUserWidgetObject();

	LightPuzzleWidget = Cast<ULightsPuzzleWidget>(widget);
	
	if(LightPuzzleWidget)
		LightPuzzleWidget->OnButtonPressed.AddDynamic(this, &ALightsPortrait::SwitchColor);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ButtonTimeLine.TickTimeline(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::SwitchColor()
{
	if(!bCanInteract) return;
	
	ButtonTimeLine.PlayFromStart();

	bCanInteract = false;

	UGameplayStatics::PlaySound2D(GetWorld(), SFX_Switch);
	ColorIndex++;

	if (ColorIndex >= SwitcheableColors.Num())
	{
		ColorIndex = 0;
	}

	Light->SetLightColor(SwitcheableColors[ColorIndex]);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::ButtonPressedTick(float deltaSeconds)
{
	auto lerped = FMath::Lerp(originalLocation, endLocation,deltaSeconds);
	Button->SetRelativeLocation(lerped);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPortrait::ButtonPressedFinished()
{
	bCanInteract = true;
}