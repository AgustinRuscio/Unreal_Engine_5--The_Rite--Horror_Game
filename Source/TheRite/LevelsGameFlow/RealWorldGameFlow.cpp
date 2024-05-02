//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "RealWorldGameFlow.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TriggerVolume.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "TheRite/AlexPlayerController.h"


ARealWorldGameFlow::ARealWorldGameFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ARealWorldGameFlow::BeginPlay()
{
	Super::BeginPlay();

	PlayerMethods();
	CreateWidgets();
	
	KnockTrigger->OnActorBeginOverlap.AddDynamic(this, &ARealWorldGameFlow::OnOverlapBeginKnock);
	

	if (!GetWorldTimerManager().IsTimerActive(ShowFirstTutorialWidget))
		GetWorldTimerManager().SetTimer(ShowFirstTutorialWidget, this, &ARealWorldGameFlow::ShowingFirstTutorialWidget, 3.0f, false);
}

void ARealWorldGameFlow::PlayerMethods()
{
	Player = CastChecked<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));
	Player->ForceTalk(FirstTalkAudio);
	Player->SetPlayerOptions(true, false);
}

//---------------- Widgets Methods
void ARealWorldGameFlow::CreateWidgets()
{
	FirstTutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), FirstTutorialMenu);
	FirstTutorialWidget->AddToViewport(0);
	FirstTutorialWidget->SetVisibility(ESlateVisibility::Hidden);
	FirstTutorialWidget->SetIsFocusable(true);

	SecondTutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), SecondsTutorialMenu);
	SecondTutorialWidget->AddToViewport(0);
	SecondTutorialWidget->SetVisibility(ESlateVisibility::Hidden);
	SecondTutorialWidget->SetIsFocusable(true);

	auto controller = GetWorld()->GetFirstPlayerController();
	
	if(auto alexController = Cast<AAlexPlayerController>(controller))
	{
		alexController->OnKeyPressed.AddDynamic(SecondTutorialWidget, &UTutorialWidget::SetKeyMode);
		alexController->OnKeyPressed.AddDynamic(FirstTutorialWidget, &UTutorialWidget::SetKeyMode);
	}
}

void ARealWorldGameFlow::ShowingFirstTutorialWidget()
{
	FirstTutorialWidget->SetVisibility(ESlateVisibility::Visible);
	
	if (!GetWorldTimerManager().IsTimerActive(HideFirstTutorialWidget))
		GetWorldTimerManager().SetTimer(HideFirstTutorialWidget, this, &ARealWorldGameFlow::HidingFirstTutorialWidget, 3.0f, false);
}

void ARealWorldGameFlow::HidingFirstTutorialWidget()
{
	FirstTutorialWidget->SetVisibility(ESlateVisibility::Hidden);
	if (!GetWorldTimerManager().IsTimerActive(ShowSecondTutorialWidget))
		GetWorldTimerManager().SetTimer(ShowSecondTutorialWidget, this, &ARealWorldGameFlow::ShowingSecondTutorialWidget, 3.0f, false);
}

void ARealWorldGameFlow::ShowingSecondTutorialWidget()
{
	SecondTutorialWidget->SetVisibility(ESlateVisibility::Visible);
	
	if (!GetWorldTimerManager().IsTimerActive(HideSecondTutorialWidget))
		GetWorldTimerManager().SetTimer(HideSecondTutorialWidget, this, &ARealWorldGameFlow::HidingSecondTutorialWidget, 3.0f, false);
}

void ARealWorldGameFlow::HidingSecondTutorialWidget()
{
	SecondTutorialWidget->SetVisibility(ESlateVisibility::Hidden);
}
	

void ARealWorldGameFlow::OnOverlapBeginKnock(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor))return;

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Knocking);
	KnockTrigger->Destroy();
}