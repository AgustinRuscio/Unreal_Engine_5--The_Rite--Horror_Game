//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "EmblemsPlace.h"

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/SimpleGrabbableActor.h"

//----------------------------------------------------------------------------------------------------------------------
AEmblemsPlace::AEmblemsPlace()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	RootComponent = MeshComponent;

	bFistInteraction = true;
	EmblemsState	 = 0;
	
	SetUpComponents();
}

//----------------------------------------------------------------------------------------------------------------------
bool AEmblemsPlace::GetIsFirstInteraction()
{
	return bFistInteraction;
}

//----------------------------------------------------------------------------------------------------------------------
int8 AEmblemsPlace::GetEmblemsState() const
{
	return EmblemsState;
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::Interaction()
{
	if(!bCanInteract) return;

	if(EmblemsPicked == 0)
	{
		if(!bFistInteraction) return;

		OnInteractionTrigger.Broadcast(this);
		bFistInteraction = false;

		return;
	}
	
	bCanInteract = false;
	++EmblemsState;
	
	auto player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
	auto currentPair = MapEmblem[0];
	CurrentEmblem = currentPair.Key;
	CurrentEndLocation = currentPair.Value;
	CurrentEmblem->SetVisibility(true);
	
	player->RemoveFromInventory(CurrentEmblemName,  CurrentEmblemId);

	PlaceEmblemTimeLine.PlayFromStart();

	MapEmblem.Remove(currentPair);
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
void AEmblemsPlace::SetUpComponents()
{
	SetUpEmblems();
	SetUpArrows();
	SetUpPairs();
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::SetUpEmblems()
{
	EmblemA = CreateDefaultSubobject<UStaticMeshComponent>("Emblem A");
	EmblemB = CreateDefaultSubobject<UStaticMeshComponent>("Emblem B");
	EmblemC = CreateDefaultSubobject<UStaticMeshComponent>("Emblem C");

	EmblemA->SetupAttachment(MeshComponent);
	EmblemA->SetVisibility(false);
	EmblemA->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	EmblemB->SetupAttachment(MeshComponent);
	EmblemB->SetVisibility(false);
	EmblemB->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	EmblemC->SetupAttachment(MeshComponent);
	EmblemC->SetVisibility(false);
	EmblemC->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::SetUpArrows()
{
	EmblemAEndLocation = CreateDefaultSubobject<UArrowComponent>("Emblem A End Location");
	EmblemBEndLocation = CreateDefaultSubobject<UArrowComponent>("Emblem B End Location");
	EmblemCEndLocation = CreateDefaultSubobject<UArrowComponent>("Emblem C End Location");

	EmblemAEndLocation->SetupAttachment(MeshComponent);
	EmblemBEndLocation->SetupAttachment(MeshComponent);
	EmblemCEndLocation->SetupAttachment(MeshComponent);
}

//----------------------------------------------------------------------------------------------------------------------
void AEmblemsPlace::SetUpPairs()
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
void AEmblemsPlace::EmblemObtained(AInteractor* Interactable)
{
	CurrentEmblemName = Interactable->GetItemName();
	CurrentEmblemId = Interactable->GetItemID();
	EmblemsPicked++;
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
	OnInteractionTrigger.Broadcast(this);
	
	bCanInteract = MapEmblem.Num() > 0;
}