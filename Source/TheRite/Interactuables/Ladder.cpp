//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Ladder.h"

#include "FrameTypes.h"
#include "LevelSequenceActor.h"
#include "Components/BoxComponent.h"
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
	
	LadderMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ladder Mesh");
	LadderTop = CreateDefaultSubobject<UStaticMeshComponent>("Ladder Top Mesh");
	
	BoxCollider= CreateDefaultSubobject<UBoxComponent>("Box collider");
	
	InitialPosition = CreateDefaultSubobject<UArrowComponent>("Initial Location Arrow");
	EndPosition = CreateDefaultSubobject<UArrowComponent>("End Location Arrow");
	
	InitialPosition->SetupAttachment(LadderMesh);
	EndPosition->SetupAttachment(LadderMesh);
	BoxCollider->SetupAttachment(LadderMesh);
}

void ALadder::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("OnReLocationPlayerTimeLineTick"));
	ReLocatePlayerTimeLine.AddInterpFloat(CurveFloat, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("OnReLocationPlayerTimeLineFinished"));
	ReLocatePlayerTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

void ALadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ReLocatePlayerTimeLine.TickTimeline(DeltaTime);
}

void ALadder::Interaction()
{
	if(!bCanInteract) return;

	bCanInteract = false;

	OnInteractionTrigger.Broadcast(this);
	
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->DisableInput(controller);

	if(bFlipFlop)
	{
		NewLocationForTransport = InitialPosition->GetComponentTransform();
		NewLocationForLooking = EndPosition->GetComponentTransform();
	}
	else
	{
		NewLocationForTransport = EndPosition->GetComponentTransform();
		NewLocationForLooking = InitialPosition->GetComponentTransform();
	}
	
	PlayerTransform = player->GetTransform();
	player->ForceLighterOff();
	
	ReLocatePlayerTimeLine.PlayFromStart();
}

void ALadder::EnableLadder()
{
	LadderTop->SetVisibility(false);
	LadderMesh->SetVisibility(true);
	
	LadderMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	LadderTop->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	bCanInteract = true;
}

void ALadder::DisableLadder()
{
	LadderTop->SetVisibility(true);
	LadderMesh->SetVisibility(false);
	
	LadderTop->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	LadderMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	bCanInteract = false;	
}

void ALadder::OnCinematicFinished()
{
	bCanInteract = true;
	
	player->SetActorTransform(NewLocationForTransport);
	player->MakeCameraView(NewLocationForTransport.GetRotation().Rotator());

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->EnableInput(controller);
	
	player->ForceHolding(false);
	bFlipFlop = !bFlipFlop;
}

void ALadder::OnReLocationPlayerTimeLineTick(float delta)
{
	auto LerpedLocation = FMath::Lerp(PlayerTransform.GetLocation(), NewLocationForLooking.GetLocation(), delta);
	player->SetActorLocation(FVector(LerpedLocation.X,LerpedLocation.Y, PlayerTransform.GetLocation().Z));

	auto LerpedRotation = FMath::Lerp(PlayerTransform.GetRotation().Rotator(), NewLocationForLooking.GetRotation().Rotator(), delta);
	player->MakeCameraView(LerpedRotation);
}

void ALadder::OnReLocationPlayerTimeLineFinished()
{
	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.PlayRate = 2.0f; 
	PlaybackSettings.bAutoPlay = true;
	PlaybackSettings.bRandomStartTime = false;
	ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	
	if(bFlipFlop)
		ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), StairsUpCinematic, PlaybackSettings,TempLevelSequenceActor);
	else
		ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), StairsDownCinematic, PlaybackSettings,TempLevelSequenceActor);
	
	TempLevelSequenceActor->GetSequencePlayer()->OnFinished.AddDynamic(this, &ALadder::OnCinematicFinished);
	TempLevelSequenceActor->GetSequencePlayer()->Play();
}
