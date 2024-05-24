//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Ladder.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Characters/Alex.h"

ALadder::ALadder()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	LadderMesh= CreateDefaultSubobject<UStaticMeshComponent>("Ladder Mesh");
	
	InitialPosition = CreateDefaultSubobject<UArrowComponent>("Initial Location Arrow");
	EndPosition = CreateDefaultSubobject<UArrowComponent>("End Location Arrow");
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	
	Camera->SetupAttachment(LadderMesh);
	InitialPosition->SetupAttachment(LadderMesh);
	EndPosition->SetupAttachment(LadderMesh);
}

void ALadder::BeginPlay()
{
	Super::BeginPlay();
}

void ALadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALadder::Interaction()
{
	if(!bCanInteract) return;

	bCanInteract = false;
	
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->DisableInput(controller);
	
	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.PlayRate = 1.0f; 
	PlaybackSettings.bAutoPlay = true;
	PlaybackSettings.bRandomStartTime = false;
	ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();

	//ULevelSequencePlayer* sequencePlayer;
	
	if(bFlipFlop)
	{
		NewLocation = InitialPosition->GetComponentTransform();
		ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), StairsUpCinematic, PlaybackSettings,TempLevelSequenceActor);
	}
	else
	{
		NewLocation = EndPosition->GetComponentTransform();
		ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), StairsDownCinematic, PlaybackSettings,TempLevelSequenceActor);
	}

	TempLevelSequenceActor->GetSequencePlayer()->OnFinished.AddDynamic(this, &ALadder::OnCinematicFinished);
	TempLevelSequenceActor->GetSequencePlayer()->Play();
}

void ALadder::OnCinematicFinished()
{
	bCanInteract = true;
	
	auto player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	player->SetActorTransform(NewLocation);
	player->MakeCameraView(NewLocation.GetRotation().Rotator());

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->EnableInput(controller);
	
	bFlipFlop = !bFlipFlop;
}