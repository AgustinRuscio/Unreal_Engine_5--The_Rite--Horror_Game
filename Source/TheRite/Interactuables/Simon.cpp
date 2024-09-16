//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "Simon.h"

#include "Components/WidgetComponent.h"
#include "TheRite/Widgets/SimonWidget.h"

static FVector CenterEndLocation;

//----------------------------------------------------------------------------------------------------------------------
ASimon::ASimon()
{
	PrimaryActorTick.bCanEverTick = true;

	SimonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Simon Mesh");
	
	CenterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Center Mesh");
	CenterMesh->SetupAttachment(SimonMesh);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	WidgetComponent->SetupAttachment(SimonMesh);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::BeginPlay()
{
	Super::BeginPlay();

	SimonWidget = Cast<USimonWidget>(WidgetComponent->GetUserWidgetObject());
	SimonWidget->OnSimonCompleted.AddDynamic(this, &ASimon::SimonCompleted);
	SimonWidget->SetWidgetParentLocation(GetActorLocation());

	CenterEndLocation = CenterMesh->GetComponentLocation() + CenterLocationToAdd;
	
	BindTimeLine();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveCenterTimeline.TickTimeline(DeltaTime);
} 

//----------------------------------------------------------------------------------------------------------------------
void ASimon::SimonCompleted()
{
	WidgetComponent->DestroyComponent();
	MoveCenterTimeline.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::BindTimeLine()
{
	FOnTimelineFloat MoveCenterTick;
	MoveCenterTick.BindUFunction(this, FName("MoveCenterTick"));
	MoveCenterTimeline.AddInterpFloat(MoveCenterCurve, MoveCenterTick);
	
	FOnTimelineEventStatic MoveCenterFinished;
	MoveCenterFinished.BindUFunction(this, FName("MoveCenterFinished"));
	MoveCenterTimeline.SetTimelineFinishedFunc(MoveCenterFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::MoveCenterTick(float deltaSeconds)
{
	auto lerpLocation = FMath::Lerp(CenterMesh->GetComponentLocation(), CenterEndLocation, deltaSeconds);
	
	CenterMesh->SetWorldLocation(lerpLocation);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::MoveCenterFinished()
{
	SimonMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CenterMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}