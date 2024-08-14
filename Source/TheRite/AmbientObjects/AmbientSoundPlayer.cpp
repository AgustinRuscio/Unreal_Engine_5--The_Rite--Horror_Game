//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "AmbientSoundPlayer.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

//*****************************Public******************************************
//*****************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AAmbientSoundPlayer::AAmbientSoundPlayer()
{
	bAllowTickBeforeBeginPlay = true;
	AudioComp = CreateDefaultSubobject<UAudioComponent>("Audio Component");
}

//----------------------------------------------------------------------------------------------------------------------
AAmbientSoundPlayer::~AAmbientSoundPlayer()
{
	if(AudioComp != nullptr)
		AudioComp->OnAudioFinished.Clear();
}

//*****************************Private******************************************
//******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AAmbientSoundPlayer::BeginPlay()
{
	Super::BeginPlay();

	CreateAudio();
}

//----------------------------------------------------------------------------------------------------------------------
void AAmbientSoundPlayer::CreateAudio()
{
	if(AudioComp != nullptr)
		AudioComp->OnAudioFinished.Clear();

	if(bIs2D)
		AudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), CueToSound);
	else
		AudioComp = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), CueToSound, GetActorLocation());
	
	AudioComp->OnAudioFinished.AddDynamic(this, &AAmbientSoundPlayer::CreateAudio);
}