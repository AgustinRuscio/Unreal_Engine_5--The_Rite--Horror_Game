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

	if(DoOnceOpenByNear) return;
	if(!bCanInteract) return;

	if(UE::Geometry::Distance(player->GetActorLocation(), GetActorLocation()) <= DistanceToNearAnim)
	{
		DoOnceOpenByNear = true;
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

	if(FirstInteraction)
	{
		LadderSkeletal->PlayAnimation(Animation_FullyOpen, false);

		if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_FullOpenAnim))
		{
			FTimerDelegate delegate;

			delegate.BindLambda([&]
			{
				FirstInteraction = false;
			});

			GetWorld()->GetTimerManager().SetTimer(Timer_FullOpenAnim, delegate, Animation_FullyOpen->GetPlayLength(), false);
		}
		
		return;
	}
	
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
	
	Timer_ReLocatePlayerTimeLine.PlayFromStart();
}

void ALadder::EnableLadder()
{
	//LadderTop->SetVisibility(false);
	//LadderMesh->SetVisibility(true);

	LadderSkeletal->SetAnimation(Animation_EnableLadder);
	LadderMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	
	LadderSkeletal->PlayAnimation(Animation_EnableLadder, false);
	auto a =Animation_EnableLadder->GetPlayLength();

	BoxCollider->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	
	//LadderMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	//LadderTop->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	bCanInteract = true;
}

void ALadder::DisableLadder()
{
	//LadderTop->SetVisibility(true);
	//LadderMesh->SetVisibility(false);

	
	LadderSkeletal->SetAnimation(Animation_DisableLadder);
	LadderSkeletal->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	//LadderTop->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	//LadderMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
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
