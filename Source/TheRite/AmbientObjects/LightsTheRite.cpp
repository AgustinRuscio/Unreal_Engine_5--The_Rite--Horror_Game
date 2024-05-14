//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "LightsTheRite.h"
#include "Components/SphereComponent.h"

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

bool ALightsTheRite::IsLightOn()
{
	return PointLight->Intensity > 0;
}

HouseZone ALightsTheRite::GetLightZone()
{
	return LightHouseZone;
}

void ALightsTheRite::BeginPlay()
{
	Super::BeginPlay();

	FirstPointIntensity= PointLight->Intensity;
}

//---------------- Material Setter Methods
void ALightsTheRite::AggresiveMatterial()
{
	PointLight->SetLightFunctionMaterial(AggresiveMaterial);
}

void ALightsTheRite::NormalMatterial()
{
	PointLight->SetLightFunctionMaterial(NormalMaterial);
}

//---------------- State Changer Methods
void ALightsTheRite::TurnOff()
{
	PointLight->SetIntensity(0.0f);
}

void ALightsTheRite::TurnOn()
{
	PointLight->SetIntensity(FirstPointIntensity != 0 ? FirstPointIntensity : DefaultLightIntensity);
}