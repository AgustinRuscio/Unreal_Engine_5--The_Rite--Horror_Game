//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "LightsTheRite.h"
#include "Components/SphereComponent.h"


//*****************************Public******************************************
//******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------
bool ALightsTheRite::IsLightOn() const
{
	return PointLight->Intensity > 0;
}

//----------------------------------------------------------------------------------------------------------------------
float ALightsTheRite::GetIntensity() const
{
	return PointLight->Intensity;
}

//----------------------------------------------------------------------------------------------------------------------
HouseZone ALightsTheRite::GetLightZone() const
{
	return LightHouseZone;
}

//----------------------------------------------------------------------------------------------------------------------
HospitalZone ALightsTheRite::GetHospitalZone() const
{
	return HospitalZone;
}

//----------------------------------------------------------------------------------------------------------------------
//---------------- Material Setter Methods
void ALightsTheRite::SetAggressiveMaterial() const
{
	PointLight->SetLightFunctionMaterial(Material_Aggressive);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsTheRite::SetNormalMaterial() const
{
	PointLight->SetLightFunctionMaterial(Material_Normal);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsTheRite::ChangeLightIntensity(float NewIntensity, bool bUseAsNewDefault)
{
	PointLight->SetIntensity(NewIntensity);

	if(!bUseAsNewDefault) return;
	
	if(FirstPointIntensity != 0)
		FirstPointIntensity = NewIntensity;
	else
		DefaultLightIntensity = NewIntensity;
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region State Changer Methods
void ALightsTheRite::TurnOff() const
{
	PointLight->SetIntensity(0.0f);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsTheRite::TurnOn() const
{
	PointLight->SetIntensity(FirstPointIntensity != 0 ? FirstPointIntensity : DefaultLightIntensity);
}
#pragma endregion

//*****************************Private******************************************
//******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ALightsTheRite::BeginPlay()
{
	Super::BeginPlay();
	
	if(bWillStartOff)
		PointLight->SetIntensity(0);
	
	FirstPointIntensity = PointLight->Intensity;
}