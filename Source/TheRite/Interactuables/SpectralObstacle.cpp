//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "SpectralObstacle.h"
#include "NiagaraComponent.h"
#include "VectorTypes.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

//*****************************Public************************************************
//***********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ASpectralObstacle::ASpectralObstacle()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	NiagaraSystemComponent = CreateDefaultSubobject<UNiagaraComponent>("Niagara System");

	NiagaraSystemComponent->SetupAttachment(BoxCollider);
}

//----------------------------------------------------------------------------------------------------------------------
# pragma region Destroy Methods
void ASpectralObstacle::DestroyObject(UNiagaraComponent* comp)
{
	FirstTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void ASpectralObstacle::ObstacleDestroy()
{
	UGameplayStatics::SpawnSound2D(GetWorld(), SpectralSound);
	
	NiagaraSystemComponent->SetIntParameter(TEXT("Loop Count"), 1.f);
	NiagaraSystemComponent->OnSystemFinished.AddDynamic(this, &ASpectralObstacle::DestroyObject);
}
#pragma endregion

//*****************************Private************************************************
//************************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ASpectralObstacle::BeginPlay()
{
	Super::BeginPlay();

	ParentStaticMesh = Cast<UStaticMeshComponent>(ParentActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	DynamicMaterial = UMaterialInstanceDynamic::Create(Mat, this);
	ParentStaticMesh->SetMaterial(0, DynamicMaterial);
	
	BindTimeLines();
}

//----------------------------------------------------------------------------------------------------------------------
void ASpectralObstacle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FirstTimeLine.TickTimeline(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region TimeLines Methods
void ASpectralObstacle::BindTimeLines()
{
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("FirstTimeLineUpdate"));
	FirstTimeLine.AddInterpFloat(BothTimeLineCurve, TimelineCallback);

	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("FirstTimelineFinished"));
	FirstTimeLine.SetTimelineFinishedFunc(TimelineFinishedCallback);
}

//----------------------------------------------------------------------------------------------------------------------
void ASpectralObstacle::FirstTimeLineUpdate(float time)
{
	float value = FMathf::Lerp(1,2,time);
	
	DynamicMaterial->SetScalarParameterValue("Corruption", value);
}	

//----------------------------------------------------------------------------------------------------------------------
void ASpectralObstacle::FirstTimelineFinished()
{
	OnObstacleDestroy.Broadcast();
	Destroy();
}
#pragma endregion