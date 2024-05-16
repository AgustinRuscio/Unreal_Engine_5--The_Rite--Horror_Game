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

	BindTimeLines();
}

void ASpectralObstacle::Tick(float DeltaSeconds)
{
	FirstTimeLine.TickTimeline(DeltaSeconds);
}

//---------------- Destroy Methods
void ASpectralObstacle::DestryoObject(UNiagaraComponent* comp)
{
	FirstTimeLine.PlayFromStart();
}

void ASpectralObstacle::ObstacleDestroy()
{
	UGameplayStatics::SpawnSound2D(GetWorld(), SpectralSound);
	
	NiagaraSystemComponent->SetIntParameter(TEXT("Loop Count"), 1.f);
	NiagaraSystemComponent->OnSystemFinished.AddDynamic(this, &ASpectralObstacle::DestryoObject);
}

//---------------- TimeLines Methods
void ASpectralObstacle::BindTimeLines()
{
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("FirstTimeLineUpdate"));
	FirstTimeLine.AddInterpFloat(BothTimeLineCurve, TimelineCallback);

	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("FirstTimelineFinished"));
	FirstTimeLine.SetTimelineFinishedFunc(TimelineFinishedCallback);
}

void ASpectralObstacle::FirstTimeLineUpdate(float time)
{
	float value = FMathf::Lerp(1,2,time);
	
	ParentStaticMesh->SetMaterial(0, DynamicMaterial);
	DynamicMaterial->SetScalarParameterValue("Corruption", value);
}	

void ASpectralObstacle::FirstTimelineFinished()
{
	OnObstacleDestroy.Broadcast();
	Destroy();
}