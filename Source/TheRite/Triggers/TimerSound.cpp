//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "TimerSound.h"

#include "Kismet/GameplayStatics.h"

ATimerSound::ATimerSound()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ATimerSound::Tick(float DeltaTime)
{
	Timer += DeltaTime;

	if(Timer < CooldDown) return;

	UGameplayStatics::SpawnSound2D(this, Sound);
	Timer = 0;
}