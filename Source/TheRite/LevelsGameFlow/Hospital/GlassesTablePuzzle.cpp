//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "GlassesTablePuzzle.h"
#include "Components/ArrowComponent.h"

namespace 
{
	FVector FirstGlassOriginalLocation;
	FVector SecondGlassOriginalLocation;
}

//----------------------------------------------------------------------------------------------------------------------
AGlassesTablePuzzle::AGlassesTablePuzzle()
{
	PrimaryActorTick.bCanEverTick = true;

	TableMesh = CreateDefaultSubobject<UStaticMeshComponent>("Table Mesh");
	RootComponent = TableMesh;

	FirstGlassMesh = CreateDefaultSubobject<UStaticMeshComponent>("First Glass Mesh");
	FirstGlassMesh->SetupAttachment(TableMesh);

	SecondGlassMesh = CreateDefaultSubobject<UStaticMeshComponent>("Second Glass Mesh");
	SecondGlassMesh->SetupAttachment(TableMesh);

	ThirdGlassMesh = CreateDefaultSubobject<UStaticMeshComponent>("Third Glass Mesh");
	ThirdGlassMesh->SetupAttachment(TableMesh);

	FirstGlassCorrectLocation = CreateDefaultSubobject<UArrowComponent>("First Glass Arrow");
	FirstGlassCorrectLocation->SetupAttachment(TableMesh);

	SecondGlassCorrectLocation = CreateDefaultSubobject<UArrowComponent>("Second Glass Arrow");
	SecondGlassCorrectLocation->SetupAttachment(TableMesh);
}

//----------------------------------------------------------------------------------------------------------------------
void AGlassesTablePuzzle::ObtainGlass()
{
	if (!bGlassReady) 
		bGlassReady = true;
	else if (!bSecondGlassReady)
		bSecondGlassReady = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AGlassesTablePuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	FirstGlassOriginalLocation  = SecondGlassMesh->GetRelativeLocation();
	SecondGlassOriginalLocation = ThirdGlassMesh->GetRelativeLocation();

	SecondGlassMesh->SetVisibility(false);
	ThirdGlassMesh->SetVisibility(false);

	//------- Glass Col timeline
	FOnTimelineFloat LockedTimelineCallback;
	LockedTimelineCallback.BindUFunction(this, FName("TimeLineTick"));
	GlassMovementTimeLine.AddInterpFloat(TimeLineCurveFloat, LockedTimelineCallback);

	FOnTimelineEventStatic LockedTimelineFinishedCallback;
	LockedTimelineFinishedCallback.BindUFunction(this, FName("TimeLineFinished"));
	GlassMovementTimeLine.SetTimelineFinishedFunc(LockedTimelineFinishedCallback);

}

//----------------------------------------------------------------------------------------------------------------------
void AGlassesTablePuzzle::Tick(float DeltaSeconds)
{
	GlassMovementTimeLine.TickTimeline(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
void AGlassesTablePuzzle::Interaction()
{
	if (!bCanInteract) return;
	
	if (bBothReady) 
	{

	}

	if (!bGlassReady && !bSecondGlassReady) return;

	bCanInteract = false;

	if (bGlassReady)
	{
		SecondGlassMesh->SetVisibility(true);
	}
	
	if (bSecondGlassReady)
	{
		ThirdGlassMesh->SetVisibility(true);
	}

	GlassMovementTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void AGlassesTablePuzzle::GlassObetain(int8 GlassIndex)
{
	bGlassReady = bGlassReady ? true : GlassIndex == 0;
	bSecondGlassReady = bSecondGlassReady ? true : GlassIndex == 1;
}

//----------------------------------------------------------------------------------------------------------------------
void AGlassesTablePuzzle::TimeLineTick(float tick)
{
	if (bGlassReady)
	{
		auto LerpedLocation = FMath::Lerp(FirstGlassOriginalLocation, FirstGlassCorrectLocation->GetRelativeLocation(), tick);

		SecondGlassMesh->SetRelativeLocation(LerpedLocation);

	}
	else if (bSecondGlassReady)
	{
		auto LerpedLocation = FMath::Lerp(SecondGlassOriginalLocation, SecondGlassCorrectLocation->GetRelativeLocation(), tick);

		ThirdGlassMesh->SetRelativeLocation(LerpedLocation);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AGlassesTablePuzzle::TimeLineFinished()
{
	if (bGlassReady)
	{
		bGlassReady = false;
	}
	else if (bSecondGlassReady)
	{
		bSecondGlassReady = false;
		bBothReady = true;
	}

	bCanInteract = true;
}