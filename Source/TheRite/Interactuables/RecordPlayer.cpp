//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "RecordPlayer.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

//*****************************Public************************************************
//***********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ARecordPlayer::ARecordPlayer()
{
 	PrimaryActorTick.bCanEverTick = true;
	Base = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	Disc = CreateDefaultSubobject<UStaticMeshComponent>("Disc");
	Latch = CreateDefaultSubobject<UStaticMeshComponent>("Latch");

	RootComponent = Base;
	
	Disc->SetupAttachment(Base);
	Latch->SetupAttachment(Base);
}

//----------------------------------------------------------------------------------------------------------------------
void ARecordPlayer::Interaction()
{
	Super::Interaction();

	bIsPaused ? PlaySong() : PauseSong();
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Action Methods
void ARecordPlayer::PlaySong()
{
	bIsPaused = false;
	AudioComponent->SetPaused(bIsPaused);
}

//----------------------------------------------------------------------------------------------------------------------
void ARecordPlayer::PauseSong()
{
	bIsPaused = true;
	AudioComponent->SetPaused(bIsPaused);
	OnSongPaused.Broadcast();
}
#pragma endregion

//*****************************Private***********************************************
//***********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ARecordPlayer::BeginPlay()
{
	Super::BeginPlay();

	AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this,Song,GetActorLocation());
	bIsPaused = true;
	AudioComponent->SetPaused(bIsPaused);
}

//----------------------------------------------------------------------------------------------------------------------
void ARecordPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(bIsPaused) return;

	Latch->AddLocalRotation(FRotator(0,0,1));
	Disc->AddLocalRotation(FRotator(0,1,0));
}