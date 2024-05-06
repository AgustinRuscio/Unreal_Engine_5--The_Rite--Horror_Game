//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Lighter.h"
#include "Components/PointLightComponent.h"
#include "SpectralWrittings.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "TheRite/Characters/Alex.h"

ALighter::ALighter()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	LighterBody = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	LighterWheel = CreateDefaultSubobject<UStaticMeshComponent>("Wheel");
	LighterTop = CreateDefaultSubobject<UStaticMeshComponent>("Top");
	PointLight = CreateDefaultSubobject<UPointLightComponent>("Point Light");

	LighterWheel->SetupAttachment(LighterBody);
	LighterTop->SetupAttachment(LighterBody);
	PointLight->SetupAttachment(LighterBody);
}

//---------------- System Class Methods
void ALighter::BeginPlay()
{
	Super::BeginPlay();
	
	CreateWidgets();

	auto alexController = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	
	if(alexController)
		alexController->OnKeyPressed.AddDynamic(TutorialWidget, &UTutorialWidget::SetKeyMode);
}

void ALighter::Interaction()
{	
	Super::Interaction();
	
	auto Player = Cast<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));

	Player->SetPlayerOptions(true, true, true);

	KeySpectralWritting->EnableInteraction();
	TutorialWidget->SetVisibility(ESlateVisibility::Visible);
	
	LighterBody->SetVisibility(false);
	LighterBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LighterWheel->SetVisibility(false);
	LighterTop->SetVisibility(false);
	PointLight->SetVisibility(false);
	
	if (!GetWorldTimerManager().IsTimerActive(TutorialTimerHanlde))
		GetWorldTimerManager().SetTimer(TutorialTimerHanlde, this, &ALighter::TurnTutorialOff, 4.f, false);
}

void ALighter::CreateWidgets()
{
	TutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), TutorialMenu);
	TutorialWidget->AddToViewport(0);
	TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
	TutorialWidget->SetIsFocusable(true);
}

void ALighter::TurnTutorialOff()
{
	TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
	
	Destroy();
}
