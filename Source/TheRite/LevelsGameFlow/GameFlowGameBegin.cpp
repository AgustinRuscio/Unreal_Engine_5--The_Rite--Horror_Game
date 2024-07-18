//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "GameFlowGameBegin.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Characters/Alex.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"

AGameFlowGameBegin::AGameFlowGameBegin()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AGameFlowGameBegin::BeginPlay()
{
	Super::BeginPlay();

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
}