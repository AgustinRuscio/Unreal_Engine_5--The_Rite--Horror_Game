//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "LockedDoor.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"

ALockedDoor::ALockedDoor()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	DoorItself = CreateDefaultSubobject<UStaticMeshComponent>("Door Itself");
	Latch = CreateDefaultSubobject<UStaticMeshComponent>("Latch");

	RootComponent = DoorItself;
	Latch->SetupAttachment(DoorItself);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");

	BoxCollision->SetupAttachment(DoorItself);
	
	bCanSoundItsLocked = true;
	bCanSound = true;
	bHasInteraction = true;
	bInteractionDone = false;
}

//---------------- System Class Methods
void ALockedDoor::BeginPlay()
{
	Super::BeginPlay();
	
	BindTimelines();
	
	Player = Cast<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));
}

void ALockedDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MyTimeline.TickTimeline(DeltaTime);
	
	if(bCanSoundItsLocked) return;

	SoundTimer = SoundTimer + DeltaTime;

	if(SoundTimer > SoundCD)
	{
		bCanSoundItsLocked = true;
		SoundTimer = 0;
	}
}

void ALockedDoor::Interaction()
{
	if(!bCanInteract) return;
	
	if(bInteractionDone)
	{
		AudioToPlay = AudioInteractionDone;
		return;
	}
	
	ItsLocked();
	
	if(!bHasInteraction) return;
	
	OnInteractionTrigger.Broadcast(this);
	
	bInteractionDone = true;
	
	OnInteraction.Broadcast();
}

//---------------- FeedBack Methods
void ALockedDoor::ItsLocked()
{
	if(AudioToPlay != nullptr)
	{
		Player->ForceTalk(AudioToPlay);
	}

	tempAudioComponent = UGameplayStatics::SpawnSound2D(this, DoorLockedSFX);
	tempAudioComponent->OnAudioFinished.AddDynamic(this, &ALockedDoor::OnAudioFinished);

	if(!bCanSoundItsLocked)
		bCanSound = true;

	MyTimeline.PlayFromStart();
}

void ALockedDoor::OnAudioFinished()
{
	bCanSound = true;
}

//---------------- TimeLine Methods
void ALockedDoor::BindTimelines()
{
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("TimeLineUpdate"));

	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("TimelineFinished"));

	MyTimeline.AddInterpFloat(MyFloatCurve, TimelineCallback);
	MyTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
}

void ALockedDoor::TimeLineUpdate(float time)
{
	float rollValue = FMath::Lerp(0.0f,5.0f, time);

	FRotator rotator = FRotator(0,rollValue,0);
		
	DoorItself->SetRelativeRotation(rotator);
}

void ALockedDoor::TimelineFinished() { }