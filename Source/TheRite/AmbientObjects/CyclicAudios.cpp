//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "CyclicAudios.h"

#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
ACyclicAudios::ACyclicAudios()
{
	PrimaryActorTick.bCanEverTick = true;

	bStartEnable 			= false;
	bSoundPlaying			= false;
	
	AudioPlayedIndex		= 0;
	OffSetTimeToNextAudio	= 0;
	TimeToNextAudio			= 0;
	TimeToNextAudioColdDown = 0;
}

//----------------------------------------------------------------------------------------------------------------------
void ACyclicAudios::Activate()
{
	PlayNextAudio();
}

//----------------------------------------------------------------------------------------------------------------------
void ACyclicAudios::PlayNextAudio()
{
	if(bSoundPlaying) return;
	
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ClueSounds[AudioPlayedIndex], GetActorLocation(), FRotator::ZeroRotator,
		1,1,0, Attenuation);

	TimeToNextAudio = ClueSounds[AudioPlayedIndex]->Duration + OffSetTimeToNextAudio;
	bSoundPlaying = true;
	
	++AudioPlayedIndex;
	if(AudioPlayedIndex >= ClueSounds.Num())
	{
		AudioPlayedIndex = 0;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ACyclicAudios::BeginPlay()
{
	Super::BeginPlay();

	if(bStartEnable) 
		Activate();
}

//----------------------------------------------------------------------------------------------------------------------
void ACyclicAudios::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(bSoundPlaying)
	{
		if(TimeToNextAudioColdDown >= TimeToNextAudio)
		{
			TimeToNextAudioColdDown = 0;
			bSoundPlaying			= false;
			PlayNextAudio();
		}
		else
		{
			TimeToNextAudioColdDown += DeltaTime;
		}
	}
}