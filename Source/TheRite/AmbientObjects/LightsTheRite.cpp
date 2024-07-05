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

bool ALightsTheRite::IsLightOn() const
{
	return PointLight->Intensity > 0;
}

float ALightsTheRite::GetIntensity() const
{
	return PointLight->Intensity;
}

HouseZone ALightsTheRite::GetLightZone() const
{
	return LightHouseZone;
}

void ALightsTheRite::BeginPlay()
{
	Super::BeginPlay();
	
	if(bWillStartOff)
		PointLight->SetIntensity(0);
	
	FirstPointIntensity = PointLight->Intensity;
}

//---------------- Material Setter Methods
void ALightsTheRite::AggressiveMaterial()
{
	PointLight->SetLightFunctionMaterial(LightMaterial_AggressiveMaterial);
}

void ALightsTheRite::NormalMaterial()
{
	PointLight->SetLightFunctionMaterial(LightMaterial_NormalMaterial);
}

void ALightsTheRite::ChangeLightIntensity(float NewIntensity, bool bUseAsNewDefault)
{
	PointLight->SetIntensity(NewIntensity);

	if(!bUseAsNewDefault) return;
	
	if(FirstPointIntensity != 0)
		FirstPointIntensity = NewIntensity;
	else
		DefaultLightIntensity = NewIntensity;
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