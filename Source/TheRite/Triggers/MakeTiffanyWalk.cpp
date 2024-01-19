#include "MakeTiffanyWalk.h"

#include "Kismet/GameplayStatics.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Characters/Alex.h"

void AMakeTiffanyWalk::FirstTimeLineUpdate(float value)
{
	for (auto Element : OtherLights)
	{
		Element->TurnOff();
	}

	for (auto Element : Lights)
	{
		Element->TurnOff();
	}
}


void AMakeTiffanyWalk::FirstTimelineFinished()
{
	SecondsTimeLine.PlayFromStart();
}

void AMakeTiffanyWalk::SecondsTimeLineUpdate(float value)
{
	for (auto Element : Lights)
	{
		Element->TurnOn();
	}
	for (auto Element : OtherLights)
	{
		Element->TurnOn();
	}

	OnFinished.Broadcast();
	Destroy();
}

void AMakeTiffanyWalk::SecondsTimelineFinished() { }

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

void AMakeTiffanyWalk::BeginPlay()
{
	Super::BeginPlay();
	BindTimeLines();
}

AMakeTiffanyWalk::AMakeTiffanyWalk()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	Box = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	Box->OnComponentBeginOverlap.AddDynamic(this, &AMakeTiffanyWalk::OnOverlapBegin);
}



void AMakeTiffanyWalk::KeyObtein(ATiffany* newTiff)
{
	Tiffany = newTiff;
	bKeyReady = true;
}

void AMakeTiffanyWalk::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAlex* AlexInside = Cast<AAlex>(OtherActor);
	
	if(!AlexInside) return;

	if(!bKeyReady) return;
	if(DoOnce > 0) return;

	DoOnce++;

	bReady = true;
	Tiffany->StartMovement(Target);

	AlexInside->CameraTargeting(Tiffany->GetActorLocation());

	UGameplayStatics::SpawnSound2D(this, SFXHeartBeat);
	UGameplayStatics::SpawnSound2D(this, SFXTiffanyNear);
}

void AMakeTiffanyWalk::Tick(float DeltaTime)
{
	FirstTimeLine.TickTimeline(DeltaTime);
	SecondsTimeLine.TickTimeline(DeltaTime);
	
	if(!bReady) return;
	
	if(FVector::Dist(Target->GetActorLocation(), Tiffany->GetActorLocation()) > 200.0f)
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
	else
	{
		FirstTimeLine.Play();
	}
}