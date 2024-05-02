//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "AmbientSoundPlayer.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

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

void AAmbientSoundPlayer::BeginPlay()
{
	Super::BeginPlay();

	CreateAudio();
}

void AAmbientSoundPlayer::CreateAudio()
{
	if(AudioComponent != nullptr)
		AudioComponent->OnAudioFinished.Clear();

	if(IsTwoDimentional)
		AudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), CueToSound);
	else
		AudioComponent = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), CueToSound, GetActorLocation());
	
	AudioComponent->OnAudioFinished.AddDynamic(this, &AAmbientSoundPlayer::CreateAudio);
}