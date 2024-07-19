//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "GameFlowGameBegin.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Characters/Alex.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "TheRite/AlexPlayerController.h"
#include "Kismet/GameplayStatics.h"

AGameFlowGameBegin::AGameFlowGameBegin()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AGameFlowGameBegin::BeginPlay()
{
	Super::BeginPlay();
	
	CreateWidgets();
	SetNeededValues();
	PlayBeginSequence();
}

void AGameFlowGameBegin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameFlowGameBegin::SetNeededValues()
{
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

void AGameFlowGameBegin::CreateWidgets()
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



void AGameFlowGameBegin::PlayBeginSequence()
{
	Player->ForceDisableInput();
	
	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.PlayRate = 1.0f; 
	PlaybackSettings.bAutoPlay = true;
	PlaybackSettings.bRandomStartTime = false;
	
	ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	
	ULevelSequencePlayer* sequencePlayer =  ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LS_BeginSequence,
																				PlaybackSettings,TempLevelSequenceActor);

	sequencePlayer->OnFinished.AddDynamic(this, &AGameFlowGameBegin::BeginSequenceFinished);
	
	sequencePlayer->Play();
}

void AGameFlowGameBegin::BeginSequenceFinished()
{
	Player->ForceEnableInput();

	ShowingFirstTutorialWidget();
}

void AGameFlowGameBegin::ShowingFirstTutorialWidget()
{
	if (!GetWorldTimerManager().IsTimerActive(ShowFirstTutorialWidget))
	{
		FTimerDelegate FirstTimer;

		FirstTimer.BindLambda([&]
		{
			FirstTutorialWidget->SetVisibility(ESlateVisibility::Visible);
	
			if (!GetWorldTimerManager().IsTimerActive(HideFirstTutorialWidget))
			{
				FTimerDelegate SecondsTimer;

				SecondsTimer.BindLambda([&]
				{
					FirstTutorialWidget->SetVisibility(ESlateVisibility::Hidden);
					
					if (!GetWorldTimerManager().IsTimerActive(ShowSecondTutorialWidget))
						GetWorldTimerManager().SetTimer(ShowSecondTutorialWidget, this, &AGameFlowGameBegin::ShowingSecondTutorialWidget, 3.0f, false);
				});
				
				GetWorldTimerManager().SetTimer(HideFirstTutorialWidget, SecondsTimer, 3.0f, false);
			}
		});
		
		GetWorldTimerManager().SetTimer(ShowFirstTutorialWidget, FirstTimer, 3.0f, false);
	}
}

void AGameFlowGameBegin::ShowingSecondTutorialWidget()
{
	SecondTutorialWidget->SetVisibility(ESlateVisibility::Visible);
	
	if (!GetWorldTimerManager().IsTimerActive(HideSecondTutorialWidget))
	{
		FTimerDelegate Delegate;
		
		Delegate.BindLambda([&]
		{
			SecondTutorialWidget->SetVisibility(ESlateVisibility::Hidden);
		});
		
		GetWorldTimerManager().SetTimer(HideSecondTutorialWidget, Delegate, 3.0f, false);
	}
}