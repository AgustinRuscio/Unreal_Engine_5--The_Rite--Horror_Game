//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "GameFlowGameBegin.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Characters/Alex.h"
#include "LevelSequencePlayer.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Characters/Tiffany.h"
#include "LevelSequenceActor.h"
#include "NiagaraComponent.h"
#include "Niagara/Public/NiagaraActor.h"
#include "TheRite/Interactuables/Clock.h"
#include "TheRite/AmbientObjects/Candle.h"
#include "Engine/StaticMeshActor.h"
#include "TheRite/Interactuables/Lighter.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "TheRite/Interactuables/Rite.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Triggers/DoorSlapper.h"

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

void AGameFlowGameBegin::SetNeededValues()
{
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	Rite->OnInteractionTrigger.AddDynamic(this, &AGameFlowGameBegin::OnRiteInteraction);

	Rite->OnObjectsObtain.AddDynamic(this, &AGameFlowGameBegin::OnRiteReady);
	
	Tiffany_Garage->Deactivate();
	Lighter->Deactivate();
	Fog->GetNiagaraComponent()->Deactivate();

	RiteMesh_Clock->GetStaticMeshComponent()->SetVisibility(false);
	RiteMesh_Diary->GetStaticMeshComponent()->SetVisibility(false);
	RiteMesh_Pacifier->GetStaticMeshComponent()->SetVisibility(false);
	
	for (auto Element : MainItems)
	{
		Element->OnInteractionTrigger.AddDynamic(FindObjectsMenuWidget, &UChangingdWidget::OnInteraction);
		Element->OnInteractionTrigger.AddDynamic(this, &AGameFlowGameBegin::OnRiteObjetObtain);
	}

	for (auto Element : CandlesGuidance)
	{
		Element->TurnOff();
		Element->Disappear();
	}

	EndDoorSlapper->Deactivate();
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

	FindObjectsMenuWidget = CreateWidget<UTutorialWidget>(GetWorld(), FindObjectsMenu);
	FindObjectsMenuWidget->AddToViewport(0);
	FindObjectsMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	FindObjectsMenuWidget->SetIsFocusable(true);
	
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
	
	FindObjectsMenuWidget->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Clue);
	
	ShowingFirstTutorialWidget();
}

void AGameFlowGameBegin::PlayRiteSequence()
{
	Player->ForceDisableInput();
	
	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.PlayRate = 1.0f; 
	PlaybackSettings.bAutoPlay = true;
	PlaybackSettings.bRandomStartTime = false;
	
	ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	
	ULevelSequencePlayer* sequencePlayer =  ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LS_RiteSequence,
																				PlaybackSettings,TempLevelSequenceActor);

	sequencePlayer->OnFinished.AddDynamic(this, &AGameFlowGameBegin::RiteSequenceFinished);
	
	sequencePlayer->Play();
}

void AGameFlowGameBegin::RiteSequenceFinished()
{
	UGameplayStatics::OpenLevel(GetWorld(),NextLevel);
}

void AGameFlowGameBegin::OnRiteInteraction(AInteractor* Interactor)
{
	FindObjectsMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	
	Tiffany_Garage->Activate();

	Player->ForceLighterOff();
	
	PlayRiteSequence();
}

void AGameFlowGameBegin::OnRiteReady()
{
	Fog->GetNiagaraComponent()->Activate();
	Lighter->Activate();
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Clue);
	
	for (auto Element : AllLights)
	{
		if(Element->GetLightZone() != HouseZone::Garage)
		{
			Element->ChangeLightIntensity(Element->GetIntensity() * 0.5f, true);
			continue;
		}
		
		Element->TurnOff();
	}
	
	for (auto Element : CandlesGuidance)
	{
		Element->TurnOn();
		Element->Appear();
	}
	
	EndDoorSlapper->Activate();
}

void AGameFlowGameBegin::OnRiteObjetObtain(AInteractor* Interactable)
{
	switch (Interactable->GetItemID())
	{
		case PickableItemsID::Clock:
			RiteMesh_Clock->GetStaticMeshComponent()->SetVisibility(true);
			break;
				
		case PickableItemsID::Diary:
			RiteMesh_Diary->GetStaticMeshComponent()->SetVisibility(true);
			break;
				
		case PickableItemsID::Pacifier:
			RiteMesh_Pacifier->GetStaticMeshComponent()->SetVisibility(true);
			break;
					
		default: ;
	}
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