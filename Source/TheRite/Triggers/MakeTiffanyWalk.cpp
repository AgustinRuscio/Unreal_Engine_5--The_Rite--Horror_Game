//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "MakeTiffanyWalk.h"

#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Characters/Tiffany.h"
#include "TheRite/Characters/Alex.h"

AMakeTiffanyWalk::AMakeTiffanyWalk()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Box = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	Box->OnComponentBeginOverlap.AddDynamic(this, &AMakeTiffanyWalk::OnOverlapBegin);
}

void AMakeTiffanyWalk::BeginPlay()
{
	Super::BeginPlay();
	BindTimeLines();
}

void AMakeTiffanyWalk::Tick(float DeltaTime)
{
	FirstTimeLine.TickTimeline(DeltaTime);
	SecondsTimeLine.TickTimeline(DeltaTime);
}

void AMakeTiffanyWalk::KeyObtein(ATiffany* newTiff)
{
	Tiffany = newTiff;
	bKeyReady = true;
}

//---------------- TimeLine Methods
void AMakeTiffanyWalk::BindTimeLines()
{
	//------------------- Open Time line
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("FirstTimeLineUpdate"));
	FirstTimeLine.AddInterpFloat(BothTimeLineCurve, TimelineCallback);

	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("FirstTimelineFinished"));
	FirstTimeLine.SetTimelineFinishedFunc(TimelineFinishedCallback);

	//------------------- Close Time line
	FOnTimelineFloat CloseTimelineCallback;
	CloseTimelineCallback.BindUFunction(this, FName("SecondsTimeLineUpdate"));
	SecondsTimeLine.AddInterpFloat(BothTimeLineCurve, CloseTimelineCallback);

	FOnTimelineEventStatic CloseTimelineFinishedCallback;
	CloseTimelineFinishedCallback.BindUFunction(this, FName("SecondsTimelineFinished"));
	SecondsTimeLine.SetTimelineFinishedFunc(CloseTimelineFinishedCallback);

}

void AMakeTiffanyWalk::FirstTimeLineUpdate(float value)
{
	if(FVector::Dist(MoveTarget->GetActorLocation(), Tiffany->GetActorLocation()) > 200.0f)
	{
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(static_cast<EObjectTypeQuery>(ECollisionChannel::ECC_WorldDynamic));
		
		TArray<AActor*> IgnoredTargtes;

		IgnoredTargtes.Add(this);
		
		TArray<AActor*> OutTragtes;

		FVector StartPosition = Tiffany->GetActorLocation();
		
		bool overlaped = UKismetSystemLibrary::SphereOverlapActors(this, StartPosition, 300.0f,
			ObjectTypes,ALightsTheRite::StaticClass(),IgnoredTargtes, OutTragtes);

		if(overlaped)
		{
			for (auto ObjectType : OutTragtes)
			{
				auto light = Cast<ALightsTheRite>(ObjectType);
				Lights.Add(light);
			}
		}
	}
}

void AMakeTiffanyWalk::FirstTimelineFinished()
{
	for (auto Element : OtherLights)
	{
		Element->TurnOff();
	}

	for (auto Element : Lights)
	{
		Element->TurnOff();
	}
	
	SecondsTimeLine.PlayFromStart();
}


void AMakeTiffanyWalk::SecondsTimeLineUpdate(float value) { }

void AMakeTiffanyWalk::SecondsTimelineFinished()
{
	for (auto Element : Lights)
	{
		Element->TurnOn();
	}
	
	for (auto Element : OtherLights)
	{
		Element->TurnOn();
	}
	
	if(bSoundAfterEvent)
		UGameplayStatics::SpawnSound2D(GetWorld(), SFX_AfterEvent);
	
	OnFinishedEvent.Broadcast();
	Destroy();
}


void AMakeTiffanyWalk::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAlex* AlexInside = Cast<AAlex>(OtherActor);
	
	if(!AlexInside) return;

	if(!bKeyReady) return;
	if(DoOnce > 0) return;

	OnStartEvent.Broadcast();
	DoOnce++;

	bReady = true;
	Tiffany->StartMovement(MoveTarget);

	UGameplayStatics::SpawnSound2D(this, SFXHeartBeat);
	UGameplayStatics::SpawnSound2D(this, SFXTiffanyNear);
	
	FirstTimeLine.Play();
}