//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "RealWorldEndGameFlow.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/AlexPlayerController.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "TheRite/AmbientObjects/CustomLight.h"
#include <Kismet/GameplayStatics.h>

//----------------------------------------------------------------------------------------------------------------------
ARealWorldEndGameFlow::ARealWorldEndGameFlow()
{
 	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldEndGameFlow::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	EndGameInteractable->OnInteractionTrigger.AddDynamic(this, &ARealWorldEndGameFlow::OnInteractableTriggered);

	PlaySequence();
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldEndGameFlow::PlaySequence()
{

	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.PlayRate = 1.0f;
	PlaybackSettings.bAutoPlay = true;
	PlaybackSettings.bRandomStartTime = false;

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->DisableInput(controller);

	ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();

	ULevelSequencePlayer* sequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceFade,
		PlaybackSettings, TempLevelSequenceActor);

	sequencePlayer->OnFinished.AddDynamic(this, &ARealWorldEndGameFlow::OnSequenceFinished);

	sequencePlayer->Play();
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldEndGameFlow::OnSequenceFinished()
{
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->EnableInput(controller);
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldEndGameFlow::TurnLightsOff()
{
	for (auto current : CustomLights)
	{
		current->TurnOff();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldEndGameFlow::OnInteractableTriggered(AInteractor* interactor)
{
	TurnLightsOff();

	Player->ForceDisableInput();
	Player->ForceTalk(SFX_Voice);

	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_Voice)) return;

	TimerDelegate_Voice.BindLambda([this]()
		{
			UGameplayStatics::PlaySound2D(GetWorld(), SFX_Shoot);

			if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_Shoot)) return;

			auto timerTime = SFX_Shoot->GetDuration() + .75f;

			TimerDelegate_Shoot.BindLambda([this]()
				{
					UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
				});

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Shoot, TimerDelegate_Shoot, timerTime, false);
		});

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Voice, TimerDelegate_Voice, SFX_Voice->GetDuration() + 0.5f, false);
}