//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "CustomLight.h"
#include "Components/SpotLightComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/Light.h"

//----------------------------------------------------------------------------------------------------------------------
ACustomLight::ACustomLight()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NewRootComponent"));
	SetRootComponent(NewRootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Lamp Mesh");
	Mesh->SetupAttachment(NewRootComponent);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetSphereRadius(177.0f);
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");
	
	Sphere->SetupAttachment(NewRootComponent);
	AudioComponent->SetupAttachment(NewRootComponent);
}

//----------------------------------------------------------------------------------------------------------------------
bool ACustomLight::IsLightOn() const
{
	return CustomLights[0]->GetLightComponent()->IsVisible();
}

//----------------------------------------------------------------------------------------------------------------------
float ACustomLight::GetIntensity() const
{
	return CustomLights[0]->GetLightComponent()->Intensity;
}

//----------------------------------------------------------------------------------------------------------------------
HouseZone ACustomLight::GetLightZone() const
{
	return LightHouseZone;
}

//----------------------------------------------------------------------------------------------------------------------
HospitalZone ACustomLight::GetHospitalZone() const
{
	return HospitalZone;
}

//----------------------------------------------------------------------------------------------------------------------
//---------------- Material Setter Methods
void ACustomLight::SetAggressiveMaterial() const
{
	for (auto current : CustomLights)
	{
		current->SetLightFunctionMaterial(Material_Aggressive);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ACustomLight::SetNormalMaterial() const
{
	for (auto current : CustomLights)
	{
		current->SetLightFunctionMaterial(Material_Normal);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ACustomLight::SetIntermitentMaterial() const
{
	for (auto current : CustomLights)
	{
		current->SetLightFunctionMaterial(Material_Intermitent);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ACustomLight::ChangeLightIntensity(float NewIntensity, bool bUseAsNewDefault)
{
	CustomLights[0]->GetLightComponent()->SetIntensity(NewIntensity);

	if(!bUseAsNewDefault) return;
	
	if(FirstPointIntensity != 0)
		FirstPointIntensity = NewIntensity;
	else
		DefaultLightIntensity = NewIntensity;
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region State Changer Methods
void ACustomLight::TurnOff() const
{
	for (auto current : CustomLights)
	{
		current->GetLightComponent()->SetVisibility(false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ACustomLight::TurnOn() const
{
	for (auto current : CustomLights)
	{
		current->GetLightComponent()->SetVisibility(true);
	}
	CustomLights[0]->GetLightComponent()->SetIntensity(FirstPointIntensity != 0 ? FirstPointIntensity : DefaultLightIntensity);
}
#pragma endregion


//----------------------------------------------------------------------------------------------------------------------
void ACustomLight::BeginPlay()
{
	Super::BeginPlay();
	
	if (bWillStartOff)
		TurnOff();
	
	FirstPointIntensity = CustomLights[0]->GetLightComponent()->Intensity;
}