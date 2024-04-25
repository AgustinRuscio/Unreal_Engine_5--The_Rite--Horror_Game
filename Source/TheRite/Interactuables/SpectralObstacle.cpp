//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "SpectralObstacle.h"
#include "NiagaraComponent.h"
#include "VectorTypes.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ASpectralObstacle::ASpectralObstacle()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	NiagaraSystemComponent = CreateDefaultSubobject<UNiagaraComponent>("Niagara System");

	NiagaraSystemComponent->SetupAttachment(BoxCollider);
}

void ASpectralObstacle::BeginPlay()
{
	Super::BeginPlay();

	ParentStaticMesh = Cast<UStaticMeshComponent>(ParentActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	DynamicMaterial = UMaterialInstanceDynamic::Create(Mat, this);
	ParentStaticMesh->SetMaterial(0, DynamicMaterial);

	
	//------------------- Open Time line
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("FirstTimeLineUpdate"));
	FirstTimeLine.AddInterpFloat(BothTimeLineCurve, TimelineCallback);

	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("FirstTimelineFinished"));
	FirstTimeLine.SetTimelineFinishedFunc(TimelineFinishedCallback);
}

void ASpectralObstacle::FirstTimelineFinished()
{
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SpectralSound, GetActorLocation());
	UE_LOG(LogTemp, Error, TEXT("Time line finished"));
	OnObstacleDestroy.Broadcast();
	Destroy();
}

void ASpectralObstacle::FirstTimeLineUpdate(float time)
{
	float value = FMathf::Lerp(1,2,time);
	
	UE_LOG(LogTemp, Error, TEXT("Tick %f"), value);
	DynamicMaterial->SetScalarParameterValue("Corruption", value);
}

void ASpectralObstacle::Tick(float DeltaSeconds)
{
	FirstTimeLine.TickTimeline(DeltaSeconds);
}

void ASpectralObstacle::ObstacleDestroy()
{
	
	UE_LOG(LogTemp, Error, TEXT("Destroy Started"));
	NiagaraSystemComponent->SetIntParameter(TEXT("Loop Count"), 1.f);
	NiagaraSystemComponent->OnSystemFinished.AddDynamic(this, &ASpectralObstacle::DestryoObject);
}

void ASpectralObstacle::DestryoObject(UNiagaraComponent* comp)
{
	FirstTimeLine.PlayFromStart();
	UE_LOG(LogTemp, Error, TEXT("Time started"));
}