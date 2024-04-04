//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "BaseDrawer.h"

void ABaseDrawer::BindTimeLines()
{
	
	//------------------- Open Time line
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OpenTimelineUpdate"));
	OpenTimeLine.AddInterpFloat(BothTimeLineCurve, TimelineCallback);

	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("TimelineFinished"));
	OpenTimeLine.SetTimelineFinishedFunc(TimelineFinishedCallback);

	//------------------- Close Time line
	FOnTimelineFloat CloseTimelineCallback;
	CloseTimelineCallback.BindUFunction(this, FName("CloseTimelineUpdate"));
	CloseTimeLine.AddInterpFloat(BothTimeLineCurve, CloseTimelineCallback);

	FOnTimelineEventStatic CloseTimelineFinishedCallback;
	CloseTimelineFinishedCallback.BindUFunction(this, FName("TimelineFinished"));
	CloseTimeLine.SetTimelineFinishedFunc(CloseTimelineFinishedCallback);

	//------------------- Wait Time line
	FOnTimelineFloat WaitTimelineCallback;
	WaitTimelineCallback.BindUFunction(this, FName("WaitTimelineUpdate"));
	WaitTimeLine.AddInterpFloat(BothTimeLineCurve, WaitTimelineCallback);

	FOnTimelineEventStatic WaitTimelineFinishedCallback;
	WaitTimelineFinishedCallback.BindUFunction(this, FName("WaitTimelineFinished"));
	WaitTimeLine.SetTimelineFinishedFunc(WaitTimelineFinishedCallback);
}

//------ Open Time line
void ABaseDrawer::OpenTimeLineUpdate(float value)
{
	
	FVector A = GetActorLocation();
	FVector B = A + MoveDir;

	FVector values = FMath::Lerp(A, B, value);
	
	SetActorRelativeLocation(values);
}


//------ Close Time line
void ABaseDrawer::CloseTimeLineUpdate(float value)
{
	FVector A = GetActorLocation();
	FVector B = A - MoveDir;

	FVector values = FMath::Lerp(A, B, value);
	
	SetActorRelativeLocation(values);
}

void ABaseDrawer::WaitTimeLineUpdate(float value) { }


void ABaseDrawer::TimelineFinished()
{
	bCanInteract = true;
}

void ABaseDrawer::WaitTimelineFinished()
{
	Destroy();
}

void ABaseDrawer::BeginPlay()
{
	Super::BeginPlay();
	BindTimeLines();
}

ABaseDrawer::ABaseDrawer()
{
 	PrimaryActorTick.bCanEverTick = true;

	DrawerModel = CreateDefaultSubobject<UStaticMeshComponent>("Drawer mesh");
	RootComponent = DrawerModel;

}

bool ABaseDrawer::IsOpen() const
{
	return bIsOpen;
}

void ABaseDrawer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	OpenTimeLine.TickTimeline(DeltaSeconds);
	CloseTimeLine.TickTimeline(DeltaSeconds);
	WaitTimeLine.TickTimeline(DeltaSeconds);
}

void ABaseDrawer::Interaction()
{
	Super::Interaction();
	
	if(!bCanInteract) return;

	if(bFlipFlop)
	{
		OnDrawerOpen.Broadcast(this);
		
		bCanInteract = false;
		bIsOpen = true;
		bFlipFlop = false;
		
		OpenTimeLine.PlayFromStart();
	}
	else
	{
		bCanInteract = false;
		bIsOpen = false;
		CloseTimeLine.PlayFromStart();
		bFlipFlop = true;
	}
}

bool ABaseDrawer::IsKeyContainer() const
{
	return bKeyConteiner;
}

void ABaseDrawer::SetKeyContainer()
{
	bKeyConteiner = true;
}

void ABaseDrawer::AddingForce()
{
	DrawerModel->SetSimulatePhysics(true);

	FVector force = ForceDir * ForceIntensity;
	
	DrawerModel->AddForce(force);

	WaitTimeLine.PlayFromStart();
}
