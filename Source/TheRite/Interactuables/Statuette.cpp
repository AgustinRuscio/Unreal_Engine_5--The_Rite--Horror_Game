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

void AStatuette::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLightIntensity = PointLight->Intensity;
	PointLight->SetIntensity(0.0);
}

void AStatuette::OpenTimeLineUpdate(float value)
{
	FVector values = FMath::Lerp(InitialObjectPosition,EndLocation, value);
	
	SetActorLocation(values);
}

void AStatuette::Interaction()
{	
	if(!bCanInteract) return;

	if(bFirstInteraction)
	{
		bCanInteract = false;
	}
	else
	{
		bCanInteract = false;
		
		PointLight->SetIntensity(InitialLightIntensity);

		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), InteractionSound, GetActorLocation());
		InteractionTimeLine.PlayFromStart();
	}
	
	OnInteractionTrigger.Broadcast(this);
}

void AStatuette::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	InteractionTimeLine.TickTimeline(DeltaSeconds);
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
	
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OpenTimeLineUpdate"));
	InteractionTimeLine.AddInterpFloat(TimeLineCurve, TimelineCallback);
	bFirstInteraction = false;
}

bool AStatuette::IsFirstInteraction() const
{
	return bFirstInteraction;
}

void AStatuette::EnableInteraction()
{
	bCanInteract = true;
}
