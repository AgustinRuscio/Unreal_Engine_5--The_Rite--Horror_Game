//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "EmblemsPlace.h"

#include "Emblem.h"
#include "Components/ArrowComponent.h"

//----------------------------------------------------------------------------------------------------------------------
AEmblemsPlace::AEmblemsPlace()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	RootComponent = MeshComponent;

	EmblemA = CreateDefaultSubobject<UStaticMeshComponent>("Emblem A");
	EmblemB = CreateDefaultSubobject<UStaticMeshComponent>("Emblem B");
	EmblemC = CreateDefaultSubobject<UStaticMeshComponent>("Emblem C");

	EmblemA->SetupAttachment(MeshComponent);
	EmblemB->SetupAttachment(MeshComponent);
	EmblemC->SetupAttachment(MeshComponent);

	EmblemAEndLocation = CreateDefaultSubobject<UArrowComponent>("Emblem A End Location");
	EmblemBEndLocation = CreateDefaultSubobject<UArrowComponent>("Emblem B End Location");
	EmblemCEndLocation = CreateDefaultSubobject<UArrowComponent>("Emblem C End Location");

	EmblemAEndLocation->SetupAttachment(MeshComponent);
	EmblemBEndLocation->SetupAttachment(MeshComponent);
	EmblemCEndLocation->SetupAttachment(MeshComponent);

	SetLocationData();
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::Interaction()
{
	if(!bCanInteract || EmblemsPickedType.Num() <= 0) return;
	
	Super::Interaction();

	bCanInteract = false;
	
	auto currentPair = MapEmblem[MapEmblem.Num()-1];

	CurrentEmblem = currentPair.Key;
	CurrentEndLocation = currentPair.Value;

	PlaceEmblemTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::BeginPlay()
{
	Super::BeginPlay();

	BindTimeline();
	
	for (auto Element : NeededEmblems)
	{
		Element->OnInteractionTrigger.AddDynamic(this, &AEmblemsPlace::EmblemObtained);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlaceEmblemTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::SetLocationData()
{
	AllEndsLocation.Add(EmblemAEndLocation);
	AllEndsLocation.Add(EmblemBEndLocation);
	AllEndsLocation.Add(EmblemCEndLocation);

	TPair<UStaticMeshComponent*, UArrowComponent*> PairA;
	PairA.Key = EmblemA;
	PairA.Value = EmblemAEndLocation;

	TPair<UStaticMeshComponent*, UArrowComponent*> PairB;
	PairB.Key = EmblemB;
	PairB.Value = EmblemBEndLocation;

	TPair<UStaticMeshComponent*, UArrowComponent*> PairC;
	PairC.Key = EmblemC;
	PairC.Value = EmblemCEndLocation;
	
	MapEmblem.Add(PairA);
	MapEmblem.Add(PairB);
	MapEmblem.Add(PairC);
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::EmblemObtained(AInteractor* Interactor)
{
	EmblemsPickedType.Add(Interactor);
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::BindTimeline()
{
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("PlaceEmblemTick"));
	PlaceEmblemTimeLine.AddInterpFloat(PlaceEmblemCurveFloat, TimelineCallback);

	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("PlaceEmblemFinished"));
	PlaceEmblemTimeLine.SetTimelineFinishedFunc(TimelineFinishedCallback);
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::PlaceEmblemTick(float deltaSeconds)
{
	auto newLocation = FMath::Lerp(CurrentEmblem->GetRelativeLocation(), CurrentEndLocation->GetRelativeLocation(), deltaSeconds);
	
	CurrentEmblem->SetRelativeLocation(newLocation);
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::PlaceEmblemFinished()
{
	bCanInteract = true;
}