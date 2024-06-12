//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "TimerSound.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"

ATimerSound::ATimerSound()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATimerSound::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	ChangeCoolDown();
}

void ATimerSound::Tick(float DeltaTime)
{
	Timer += DeltaTime;

	if(Timer < CooldDown) return;
	
	SpawnAudio();
}

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

void ATimerSound::SpawnAudio()
{
	auto playerPosition = Player->GetActorLocation() ;
	auto forwardMinus = (Player->GetActorLocation().X - 500);

	auto audioPosition = FVector(forwardMinus, playerPosition.Y, playerPosition.Z);

	UGameplayStatics::SpawnSoundAtLocation(this, CurrentAudio(), audioPosition);

	ChangeCoolDown();
	Timer = 0;
}