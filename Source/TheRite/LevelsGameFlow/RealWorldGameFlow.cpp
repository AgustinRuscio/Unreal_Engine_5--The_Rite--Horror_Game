#include "RealWorldGameFlow.h"

#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"


ARealWorldGameFlow::ARealWorldGameFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ARealWorldGameFlow::OpenArtRoomDoor()
{ 
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_DoorOpening);
	Player->ForceTalk(ReactToLockedDoorAudio);
	
	ArtRoomDoor->Open();
	bCloseDoor = true;

	for (auto Element : ArtRoomRedLights)
	{
		Element->SpotLightComponent->SetIntensity(1000.0f);
	}
}

void ARealWorldGameFlow::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || !bCloseDoor || DoOnce > 0) return;

	++DoOnce;
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_SlamDoor);
	ArtRoomDoor->HardClosing();
	
	OnCloseTimeline.Play();
}



void ARealWorldGameFlow::BindTimeLine()
{
	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("OnCloseTimeLineFinished"));
	OnCloseTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
}


void ARealWorldGameFlow::OnCloseTimeLineFinished()
{
	ArtRoomTiffany->Destroy();

	for (auto Element : ArtRoomRedLights)
	{
		Element->Destroy();
	}

	ArtRoomDoor->SetLockedState(false);
	SlamDoorTriggerVolume->Destroy();
}
void ARealWorldGameFlow::GetPlayer()
{
	auto tempSearch = UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass());
	Player = CastChecked<AAlex>(tempSearch);
}


void ARealWorldGameFlow::BeginPlay()
{
	Super::BeginPlay();
	
	SlamDoorTriggerVolume->OnActorBeginOverlap.AddDynamic(this, &ARealWorldGameFlow::OnOverlapBegin);
	
	BindTimeLine();
	GetPlayer();
	
	Player->ForceTalk(FirstTalkAudio);

	LockedInteractionDoor->OnInteraction.AddDynamic(this, &ARealWorldGameFlow::OpenArtRoomDoor);
}

void ARealWorldGameFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnCloseTimeline.TickTimeline(DeltaTime);
}