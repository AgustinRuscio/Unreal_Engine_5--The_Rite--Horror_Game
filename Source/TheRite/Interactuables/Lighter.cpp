#include "Lighter.h"

#include "TheRite/AlexPlayerController.h"

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

void ALighter::TurnTutorialOff()
{
	
	TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
	
	Destroy();
}

void ALighter::BeginPlay()
{
	Super::BeginPlay();
	
	TutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), TutorialMenu);
	TutorialWidget->AddToViewport(0);
	TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
	TutorialWidget->SetIsFocusable(true);

	auto controller = GetWorld()->GetFirstPlayerController();
	
	if(auto alexController = Cast<AAlexPlayerController>(controller))
	{
		alexController->OnKeyPressed.AddDynamic(TutorialWidget, &UTutorialWidget::SetKeyMode);
	}
}

void ALighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALighter::Interaction()
{	
	Super::Interaction();

	RedDoor->SetCanInteract(true);
	
	TutorialWidget->SetVisibility(ESlateVisibility::Visible);
	
	LighterBody->SetVisibility(false);
	LighterBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LighterWheel->SetVisibility(false);
	LighterTop->SetVisibility(false);
	PointLight->SetVisibility(false);
	
	if (!GetWorldTimerManager().IsTimerActive(TutorialTimerHanlde))
		GetWorldTimerManager().SetTimer(TutorialTimerHanlde, this, &ALighter::TurnTutorialOff, 2.f, false);
}
