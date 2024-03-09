#include "LightsTheRite.h"

ALightsTheRite::ALightsTheRite()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NewRootComponent"));
	SetRootComponent(NewRootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Lamp Mesh");
	Mesh->SetupAttachment(NewRootComponent);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetSphereRadius(177.0f);
	
	PointLight = CreateDefaultSubobject<UPointLightComponent>("Point Light");


	PointLight->SetupAttachment(NewRootComponent);
	Sphere->SetupAttachment(NewRootComponent);
}

void ALightsTheRite::BeginPlay()
{
	Super::BeginPlay();

	FirstPointIntensity= PointLight->Intensity;
}

void ALightsTheRite::AggresiveMatterial()
{
	PointLight->SetLightFunctionMaterial(AggresiveMaterial);
}

void ALightsTheRite::NormalMatterial()
{
	PointLight->SetLightFunctionMaterial(NormalMaterial);
}

void ALightsTheRite::TurnOff()
{
	PointLight->SetIntensity(0.0f);
}

void ALightsTheRite::TurnOn()
{
	PointLight->SetIntensity(FirstPointIntensity);
}