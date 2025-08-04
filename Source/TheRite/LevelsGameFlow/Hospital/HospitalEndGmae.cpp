//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "HospitalEndGmae.h"
#include "Engine/TriggerBox.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include <TheRite/AlexPlayerController.h>
#include <TheRite/AmbientObjects/CustomLight.h>
#include <TheRite/Characters/Alex.h>
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/Emblem/EmblemsPlace.h"
#include <Kismet/GameplayStatics.h>

//----------------------------------------------------------------------------------------------------------------------

AHospitalEndGmae::AHospitalEndGmae() : NextLevelName("RealWorld_EndGame")
{
	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
void AHospitalEndGmae::BeginPlay()
{
	Super::BeginPlay();
	
	EmblemPlace->OnEndGame.AddDynamic(this, &AHospitalEndGmae::OnAllEmblesPlaced);
	EndGameBox->OnActorBeginOverlap.AddDynamic(this, &AHospitalEndGmae::BeginOverlap);
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

//----------------------------------------------------------------------------------------------------------------------
void AHospitalEndGmae::OnAllEmblesPlaced()
{
	LastDoor->SetLockedState(false);
	LastDoor->Open();;
	LastDoor->SetCanInteract(false);

	Player->SetCanUseLighterState(false);
	Player->ForceLighterOff();

	for (auto current : NearDoors)
	{
		current->HardClosing();
	}

	for (auto current : NearLights)
	{
		current->SetIntermitentMaterial();
	}

	UGameplayStatics::PlaySound2D(GetWorld(), EndGameSound);
}

//----------------------------------------------------------------------------------------------------------------------
void AHospitalEndGmae::BeginOverlap(AActor* OverlapedActor, AActor* OtherActor)
{	
	if (auto player = Cast<AAlex>(OtherActor))
	{
		LastDoor->HardClosing();

		auto playerController = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
		playerController->DisableInput(playerController);

		FMovieSceneSequencePlaybackSettings PlaybackSettings;
		PlaybackSettings.PlayRate = 1.0f;
		PlaybackSettings.bAutoPlay = true;
		PlaybackSettings.bRandomStartTime = false;

		auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
		controller->DisableInput(controller);

		ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();

		ULevelSequencePlayer* sequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceHospitalEnd,
			PlaybackSettings, TempLevelSequenceActor);

		sequencePlayer->OnFinished.AddDynamic(this, &AHospitalEndGmae::ChangeLevel);

		sequencePlayer->Play();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AHospitalEndGmae::ChangeLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
}