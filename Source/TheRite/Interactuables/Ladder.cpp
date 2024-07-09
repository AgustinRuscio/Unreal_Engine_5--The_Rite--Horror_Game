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
	
	LadderSkeletal = CreateDefaultSubobject<USkeletalMeshComponent>("Ladder");
	LadderSkeletal->SetupAttachment(LadderMesh);
	
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
	Timer_ReLocatePlayerTimeLine.AddInterpFloat(CurveFloat, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("OnReLocationPlayerTimeLineFinished"));
	Timer_ReLocatePlayerTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

void ALadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer_ReLocatePlayerTimeLine.TickTimeline(DeltaTime);

	if(bDoOnceOpenByNear) return;
	if(!bCanInteract) return;

	if(UE::Geometry::Distance(player->GetActorLocation(), GetActorLocation()) <= DistanceToNearAnim)
	{
		bDoOnceOpenByNear = true;
		bCanInteract = false;
		
		LadderSkeletal->PlayAnimation(Animation_PartialOpen, false);

		if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_PartialOpenAnim))
		{
			FTimerDelegate delegate;

			delegate.BindLambda([&]
			{
				bCanInteract = true;
			});

			GetWorld()->GetTimerManager().SetTimer(Timer_PartialOpenAnim, delegate, Animation_PartialOpen->GetPlayLength(), false);
		}
	}
}

void ALadder::Interaction()
{
	if(!bCanInteract) return;

	bFirstInteraction ? FirstInteraction() : NormalInteraction();
	
}

void ALadder::FirstInteraction()
{
	LadderSkeletal->PlayAnimation(Animation_FullyOpen, false);
	bCanInteract = false;
	if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_FullOpenAnim))
	{
		FTimerDelegate delegate;

		delegate.BindLambda([&]
		{
			bFirstInteraction = false;
			bCanInteract = true;
		});

		GetWorld()->GetTimerManager().SetTimer(Timer_FullOpenAnim, delegate, Animation_FullyOpen->GetPlayLength(), false);
	}
}

void ALadder::NormalInteraction()
{
	bCanInteract = false;

	OnInteractionTrigger.Broadcast(this);
	
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->DisableInput(controller);

	if(bFlipFlop)
	{
		NewPlayerLocation = InitialPosition->GetComponentLocation();
		NewPlayerRotation = InitialPosition->GetComponentRotation();

		POVLocation = EndPosition->GetComponentLocation();
		POVRotation = EndPosition->GetComponentRotation();
	}
	else
	{
		NewPlayerLocation = EndPosition->GetComponentLocation();
		NewPlayerRotation = EndPosition->GetComponentRotation();
		
		POVLocation = InitialPosition->GetComponentLocation();
		POVRotation = InitialPosition->GetComponentRotation();
	}
	
	PlayerTransform = player->GetTransform();
	player->ForceLighterOff();
	
	Timer_ReLocatePlayerTimeLine.PlayFromStart();
}

void ALadder::EnableLadder()
{
	LadderSkeletal->SetAnimation(Animation_EnableLadder);
	LadderSkeletal->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	
	LadderSkeletal->PlayAnimation(Animation_EnableLadder, false);

	BoxCollider->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	
	bCanInteract = true;
}

void ALadder::DisableLadder()
{
	LadderSkeletal->SetAnimation(Animation_DisableLadder);
	LadderSkeletal->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	bCanInteract = false;	
}

void ALadder::OnCinematicFinished()
{
	bCanInteract = true;
	
	player->SetActorLocation(NewPlayerLocation);
	player->SetActorRotation(NewPlayerRotation);
	player->MakeCameraView(NewPlayerRotation);

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->EnableInput(controller);
	
	player->ForceHolding(false);
	bFlipFlop = !bFlipFlop;
}

void ALadder::OnReLocationPlayerTimeLineTick(float delta)
{
	auto LerpedLocation = FMath::Lerp(PlayerTransform.GetLocation(), POVLocation, delta);
	player->SetActorLocation(FVector(LerpedLocation.X,LerpedLocation.Y, PlayerTransform.GetLocation().Z));

	auto LerpedRotation = FMath::Lerp(PlayerTransform.GetRotation().Rotator(), POVRotation, delta);
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