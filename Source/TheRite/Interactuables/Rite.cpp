#include "Rite.h"

#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"


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

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->DisableInput(controller);
	
	ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	
	ULevelSequencePlayer* sequencePlayer =  ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceFade,
																				PlaybackSettings,TempLevelSequenceActor);

	sequencePlayer->OnFinished.AddDynamic(this, &ARite::ChangeLevel);
	
	sequencePlayer->Play();
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