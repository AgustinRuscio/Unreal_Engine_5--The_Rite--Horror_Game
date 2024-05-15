//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Statuette.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"

AStatuette::AStatuette()
{
 	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
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

FRotator AStatuette::GetRotation() const
{
	return GetActorRotation();
}

//---------------- System Class Methods
void AStatuette::BeginPlay()
{
	Super::BeginPlay();

	Material = StaticMesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	StaticMesh->SetMaterial(0, DynamicMaterial);
	
	DynamicMaterial->SetScalarParameterValue(TEXT("Interaction"),1);
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
	{
		bCanInteract = false;
		DynamicMaterial->SetScalarParameterValue(TEXT("Interaction"),0);
	}
	else
	{
		bCanInteract = false;
		
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
	auto matValue = FMath::Lerp(0,1, value);

	DynamicMaterial->SetScalarParameterValue(TEXT("Interaction"),matValue);
	
	SetActorLocation(values);
}