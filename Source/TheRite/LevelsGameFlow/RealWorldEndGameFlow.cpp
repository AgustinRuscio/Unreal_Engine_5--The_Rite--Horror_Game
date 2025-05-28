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
#include "Components/AudioComponent.h"
#include <Kismet/GameplayStatics.h>

//----------------------------------------------------------------------------------------------------------------------
ARealWorldEndGameFlow::ARealWorldEndGameFlow() : VolumeEndGameSound(.7f)
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

	Player->ToggleDotUI(false);
	ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();

	ULevelSequencePlayer* sequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceFade,
		PlaybackSettings, TempLevelSequenceActor);

	sequencePlayer->OnFinished.AddDynamic(this, &ARealWorldEndGameFlow::OnSequenceFinished);

	sequencePlayer->Play();
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldEndGameFlow::OnSequenceFinished()
{
	Player->ToggleDotUI(true);
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
	Player->ToggleDotUI(false);

	auto endGameSong =UGameplayStatics::SpawnSound2D(GetWorld(), SFX_EndMusic);
	endGameSong->SetVolumeMultiplier(VolumeEndGameSound);

	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.PlayRate = 1.0f;
	PlaybackSettings.bAutoPlay = true;
	PlaybackSettings.bRandomStartTime = false;

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->DisableInput(controller);

	ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();

	ULevelSequencePlayer* sequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceShoot,
		PlaybackSettings, TempLevelSequenceActor);

	sequencePlayer->Play();
}