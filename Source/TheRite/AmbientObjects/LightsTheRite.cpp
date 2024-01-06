#include "LightsTheRite.h"

ALightsTheRite::ALightsTheRite()
{
 	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetSphereRadius(177.0f);
	
	SpotLight = CreateDefaultSubobject<USpotLightComponent>("Spot Light");
	PointLight = CreateDefaultSubobject<UPointLightComponent>("Point Light");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Lamp Mesh");
	RootComponent = Mesh;

	SpotLight->SetupAttachment(Mesh);
	PointLight->SetupAttachment(Mesh);
	Sphere->SetupAttachment(Mesh);
}

void ALightsTheRite::BeginPlay()
{
	Super::BeginPlay();

	FirstStopIntensity = SpotLight->Intensity;
	FirstPointIntensity= PointLight->Intensity;
}

void ALightsTheRite::AggresiveMatterial()
{
	SpotLight->SetLightFunctionMaterial(AggresiveMaterial);
	PointLight->SetLightFunctionMaterial(AggresiveMaterial);
}

void ALightsTheRite::NormalMatterial()
{
	SpotLight->SetLightFunctionMaterial	(NormalMaterial);
	PointLight->SetLightFunctionMaterial(NormalMaterial);
}

void ALightsTheRite::TurnOff()
{
	SpotLight->SetIntensity(0.0f);
	PointLight->SetIntensity(0.0f);
}

void ALightsTheRite::TurnOn()
{
	SpotLight->SetIntensity(FirstStopIntensity);
	PointLight->SetIntensity(FirstPointIntensity);
}