//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//


#include "AmbientSoundPlayer.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

//*****************************Public******************************************
//*****************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AAmbientSoundPlayer::AAmbientSoundPlayer() : bCreateOnBeginPlay(true), bLoop(true), bIs2D(false)
{
	bAllowTickBeforeBeginPlay = false;
	AudioComp = CreateDefaultSubobject<UAudioComponent>("Audio Component");
}

//----------------------------------------------------------------------------------------------------------------------
void AAmbientSoundPlayer::StartAudioManually(bool loop, bool global)
{
	bLoop = loop;
	bIs2D = global;

	CreateAudio();
}

//----------------------------------------------------------------------------------------------------------------------
void AAmbientSoundPlayer::StopAudios()
{
	if (AudioComp != nullptr)
	{
		if (AudioComp->OnAudioFinished.IsBound())
			AudioComp->OnAudioFinished.RemoveDynamic(this, &AAmbientSoundPlayer::CreateAudio);

		AudioComp->Stop();
	}
}

//*****************************Private******************************************
//******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AAmbientSoundPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (bCreateOnBeginPlay)
		CreateAudio();
}

//----------------------------------------------------------------------------------------------------------------------
void AAmbientSoundPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (AudioComp != nullptr)
	{
		if(AudioComp->OnAudioFinished.IsBound())
			AudioComp->OnAudioFinished.RemoveDynamic(this, &AAmbientSoundPlayer::CreateAudio);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AAmbientSoundPlayer::CreateAudio()
{
	if(AudioComp != nullptr)
		AudioComp->OnAudioFinished.RemoveDynamic(this, &AAmbientSoundPlayer::CreateAudio);

	if(bIs2D)
		AudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), CueToSound);
	else
		AudioComp = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), CueToSound, GetActorLocation());
	
	if(bLoop)
		AudioComp->OnAudioFinished.AddDynamic(this, &AAmbientSoundPlayer::CreateAudio);
}