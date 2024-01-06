#include "Rite.h"

#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"


ARite::ARite()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Plane");
	RootComponent = Mesh;
}

void ARite::BeginPlay()
{
	Super::BeginPlay();

	OnClockGain.AddDynamic(this, &ARite::CheckAudio);
	OnClockGain.Broadcast();
}

void ARite::Interaction()
{
	if(!bClockReady) return;
	
	UGameplayStatics::PlaySound2D(this, PortalAudio);

	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.PlayRate = 1.0f; 
	PlaybackSettings.bAutoPlay = true;
	PlaybackSettings.bRandomStartTime = false;
	
	ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	
	ULevelSequencePlayer* player =  ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceFade,
																				PlaybackSettings,TempLevelSequenceActor);

	player->OnFinished.AddDynamic(this, &ARite::ChangeLevel);
	
	player->Play();
}

void ARite::SetClockReady()
{
	bClockReady = true;
}

void ARite::CheckAudio()
{
	if(bClockReady)
		AudioToPlay = AudioClockReady;
	else
		AudioToPlay = AudioClockNotReady;
}

void ARite::ChangeLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(),NextLevel);
}