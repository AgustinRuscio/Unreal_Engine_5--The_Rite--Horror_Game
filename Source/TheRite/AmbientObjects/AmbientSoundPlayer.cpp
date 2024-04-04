//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "AmbientSoundPlayer.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

AAmbientSoundPlayer::AAmbientSoundPlayer()
{
}

void AAmbientSoundPlayer::BeginPlay()
{
	Super::BeginPlay();

	CreateAudio();
}

void AAmbientSoundPlayer::CreateAudio()
{
	AudioComponent = nullptr;

	if(isTwoDimentional)
		AudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), CueToSound);
	else
		AudioComponent = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), CueToSound, GetActorLocation());
	
	AudioComponent->OnAudioFinished.AddDynamic(this, &AAmbientSoundPlayer::CreateAudio);
}