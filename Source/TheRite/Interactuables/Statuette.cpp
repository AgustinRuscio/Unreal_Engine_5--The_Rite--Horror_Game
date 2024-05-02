//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Statuette.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

AStatuette::AStatuette()
{
 	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	PointLight = CreateDefaultSubobject<UPointLightComponent>("PoinLight");
	
	PointLight->SetupAttachment(StaticMesh);
}

//---------------- Getter Methods
bool AStatuette::IsFirstInteraction() const
{
	return bFirstInteraction;
}

float AStatuette::GetDesiredRotation() const
{
	return DesireRotation;
}

float AStatuette::GetRotatioToAdd() const
{
	return RotationToAdd;
}

//---------------- System Class Methods
void AStatuette::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLightIntensity = PointLight->Intensity;
	PointLight->SetIntensity(0.0);
}

void AStatuette::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	InteractionTimeLine.TickTimeline(DeltaSeconds);
}

void AStatuette::Interaction()
{	
	if(!bCanInteract) return;

	if(bFirstInteraction)
		bCanInteract = false;
	else
	{
		bCanInteract = false;
		
		PointLight->SetIntensity(InitialLightIntensity);

		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), InteractionSound, GetActorLocation());
		InteractionTimeLine.PlayFromStart();
	}
	
	OnInteractionTrigger.Broadcast(this);
}

//---------------- Action Methods
void AStatuette::EnableInteraction()
{
	bCanInteract = true;
}

void AStatuette::RestoreInitialValues()
{
	bCanInteract = true;
	PointLight->SetIntensity(0.0);
	InteractionTimeLine.ReverseFromEnd();
}

void AStatuette::SetAltarPosition(FVector pos, FRotator rot)
{
	SetActorLocation(pos);
	SetActorRotation(rot);
	
	InitialObjectPosition = GetActorLocation();
	
	EndLocation = InitialObjectPosition + MoveDir;
	
	BindTimeLine();
	bFirstInteraction = false;
}

//---------------- TimeLine Methods
void AStatuette::BindTimeLine()
{
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OpenTimeLineUpdate"));
	InteractionTimeLine.AddInterpFloat(TimeLineCurve, TimelineCallback);
}

void AStatuette::OpenTimeLineUpdate(float value)
{
	FVector values = FMath::Lerp(InitialObjectPosition,EndLocation, value);
	
	SetActorLocation(values);
}