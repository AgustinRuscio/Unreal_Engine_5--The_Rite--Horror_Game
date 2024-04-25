//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "SpawnTiffanyInTime.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"

ASpawnTiffanyInTime::ASpawnTiffanyInTime()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	Box = CreateDefaultSubobject<UBoxComponent>("Box collision");
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ASpawnTiffanyInTime::OnOverlapBegin);
}

void ASpawnTiffanyInTime::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AAlex>(OtherActor)) return;;

	bAlexInsede = true;
	UGameplayStatics::SpawnSound2D(this, TiffanyTalk);
}

void ASpawnTiffanyInTime::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if(!Cast<AAlex>(OtherActor)) return;
	
	bAlexInsede = false;
	Timer = 0;
}


void ASpawnTiffanyInTime::Tick(float DeltaTime)
{
	if(!bAlexInsede) return;

	if(!SetTimer(DeltaTime)) return;

	Timer = 0;
	UGameplayStatics::SpawnSound2D(this, TiffanyTalk);
}

bool ASpawnTiffanyInTime::SetTimer(float DeltaTime)
{
	Timer += DeltaTime;

	return Timer > TimerCD;
}