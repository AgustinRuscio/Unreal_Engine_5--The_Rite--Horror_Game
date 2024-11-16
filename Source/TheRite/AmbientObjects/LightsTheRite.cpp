//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "LightsTheRite.h"

#include "Components/SpotLightComponent.h"
#include "Components/AudioComponent.h"
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
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");
	
	PointLight->SetupAttachment(NewRootComponent);
	Sphere->SetupAttachment(NewRootComponent);
	AudioComponent->SetupAttachment(NewRootComponent);
}

//----------------------------------------------------------------------------------------------------------------------
bool ALightsTheRite::IsLightOn() const
{
	//return PointLight->Intensity > 0;
	return PointLight->IsVisible();
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
	PointLight->SetVisibility(false);
	//PointLight->SetIntensity(0.0f);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsTheRite::TurnOn() const
{
	PointLight->SetVisibility(true);
	PointLight->SetIntensity(FirstPointIntensity != 0 ? FirstPointIntensity : DefaultLightIntensity);
	//PointLight->SetIntensity(FirstPointIntensity != 0 ? FirstPointIntensity : DefaultLightIntensity);
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