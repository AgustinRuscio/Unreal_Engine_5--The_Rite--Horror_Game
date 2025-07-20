//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "Lighter.h"
#include "Components/PointLightComponent.h"
#include "SpectralWrittings.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "TheRite/Characters/Alex.h"

//----------------------------------------------------------------------------------------------------------------------
ALighter::ALighter()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	LighterBody = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	LighterWheel = CreateDefaultSubobject<UStaticMeshComponent>("Wheel");
	LighterTop = CreateDefaultSubobject<UStaticMeshComponent>("Top");
	PointLight = CreateDefaultSubobject<UPointLightComponent>("Point Light");

	LighterWheel->SetupAttachment(LighterBody);
	LighterTop->SetupAttachment(LighterBody);
	PointLight->SetupAttachment(LighterBody);
}

//----------------------------------------------------------------------------------------------------------------------
void ALighter::Interaction()
{	
	Super::Interaction();
	
	auto Player = Cast<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));

	Player->SetPlayerOptions(bWillPlayerRun, true, bWillShowReminder);

	KeySpectralWritting->EnableInteraction();

	PushWidget();

	LighterBody->SetVisibility(false);
	LighterBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LighterWheel->SetVisibility(false);
	LighterTop->SetVisibility(false);
	PointLight->SetVisibility(false);
	
	if (!GetWorldTimerManager().IsTimerActive(TutorialTimerHanlde))
		GetWorldTimerManager().SetTimer(TutorialTimerHanlde, this, &ALighter::TurnTutorialOff, TutorialWidget->GetHideTime(), false);
}

//----------------------------------------------------------------------------------------------------------------------
void ALighter::Activate()
{
	Super::Activate();
	
	LighterBody->SetVisibility(true);
	LighterBody->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	LighterWheel->SetVisibility(true);
	LighterTop->SetVisibility(true);
	PointLight->SetVisibility(true);
}

//----------------------------------------------------------------------------------------------------------------------
void ALighter::Deactivate()
{
	Super::Deactivate();
	
	LighterBody->SetVisibility(false);
	LighterBody->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	LighterWheel->SetVisibility(false);
	LighterTop->SetVisibility(false);
	PointLight->SetVisibility(false);
}

//----------------------------------------------------------------------------------------------------------------------
void ALighter::PushWidget()
{
	auto alexController = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());

	auto pushedWidget = alexController->PushWidget(TutorialMenu, true);
	TutorialWidget = Cast<UTutorialWidget>(pushedWidget);

	if (alexController)
		alexController->OnKeyPressed.AddDynamic(TutorialWidget, &UTutorialWidget::SetKeyMode);
}

//----------------------------------------------------------------------------------------------------------------------
void ALighter::TurnTutorialOff()
{
	Destroy();
}