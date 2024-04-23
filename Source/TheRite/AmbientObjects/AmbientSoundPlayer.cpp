//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "AmbientSoundPlayer.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"



void AAmbientSoundPlayer::BeginPlay()
{
	Super::BeginPlay();

	CreateAudio();
}

AAmbientSoundPlayer::AAmbientSoundPlayer()
{
	bAllowTickBeforeBeginPlay = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");
}

AAmbientSoundPlayer::~AAmbientSoundPlayer()
{
	if(AudioComponent != nullptr)
		AudioComponent->OnAudioFinished.Clear();
}

void AAmbientSoundPlayer::CreateAudio()
{
	if(AudioComponent != nullptr)
		AudioComponent->OnAudioFinished.Clear();

	if(isTwoDimentional)
		AudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), CueToSound);
	else
		AudioComponent = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), CueToSound, GetActorLocation());
	
	AudioComponent->OnAudioFinished.AddDynamic(this, &AAmbientSoundPlayer::CreateAudio);
}