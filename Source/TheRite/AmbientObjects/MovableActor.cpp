//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "MovableActor.h"

#include "LightsTheRite.h"
#include "Components/AudioComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

static FVector StartPoint;

//----------------------------------------------------------------------------------------------------------------------
AMovableActor::AMovableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	RootComponent = MeshComponent;
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");
	AudioComponent->SetupAttachment(MeshComponent);

	AudioComponent->SetActive(false);
}

//----------------------------------------------------------------------------------------------------------------------
void AMovableActor::Trigger()
{
	Super::Trigger();
	StartPoint = GetActorLocation();
	MoveTimeLine.PlayFromStart();
	PlayBeginFeedBack();
}

//----------------------------------------------------------------------------------------------------------------------
void AMovableActor::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OnMovingTick"));
	MoveTimeLine.AddInterpFloat(CurveFloat, TimelineCallback);

	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("OnMovementFinished"));
	MoveTimeLine.SetTimelineFinishedFunc(TimelineFinishedCallback);
}

//----------------------------------------------------------------------------------------------------------------------
void AMovableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void AMovableActor::PlayBeginFeedBack()
{
	AudioComponent->SetSound(SFX_Movement);
	AudioComponent->Play();
	
	for (auto Element : NearLights)
	{
		Element->SetAggressiveMaterial();
		
		if(FMath::RandRange(0, 1) == 1)
		{
			Element->TurnOff();
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AMovableActor::PlayEndFeedBack()
{
	if(AudioComponent->IsPlaying())
		AudioComponent->Stop();
	
	AudioComponent->SetSound(SFX_MovementFinished);
	AudioComponent->Play();
	
	for (auto Element : NearLights)
	{
		Element->SetNormalMaterial();
		Element->TurnOn();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AMovableActor::OnMovingTick(float DeltaTime)
{
	auto LerpLocation = FMath::LerpStable(StartPoint, EndLocation->GetActorLocation(), DeltaTime);
	SetActorLocation(LerpLocation);
}

//----------------------------------------------------------------------------------------------------------------------
void AMovableActor::OnMovementFinished()
{
	PlayEndFeedBack();
}