//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "TimerSound.h"

#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"


USoundBase* ATimerSound::CurrentAudio() const
{
	int8 rand = FMath::RandRange(0, PosibleSounds.Num()-1);
	auto curretnAudio = PosibleSounds[rand];
	curretnAudio->AttenuationSettings = FxAttenuation;
	return curretnAudio;
}

void ATimerSound::ChangeCoolDown()
{
	CooldDown = FMath::RandRange(MinCoolDown, MaxCooldDown);
}

ATimerSound::ATimerSound()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ATimerSound::BeginPlay()
{
	Super::BeginPlay();
	ChangeCoolDown();
}

void ATimerSound::Tick(float DeltaTime)
{
	Timer += DeltaTime;

	if(Timer < CooldDown) return;

	auto playerLocation = Cast<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));

	auto playerPosition = playerLocation->GetActorLocation() ;
	auto forwardMinus = (playerLocation->GetActorLocation().X - 500);

	auto audioPosition = FVector(forwardMinus, playerPosition.Y, playerPosition.Z);

	UGameplayStatics::SpawnSoundAtLocation(this, CurrentAudio(), audioPosition);

	ChangeCoolDown();
	Timer = 0;
}