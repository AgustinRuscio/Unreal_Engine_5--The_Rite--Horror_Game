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
	return CustomLight->GetLightComponent()->IsVisible();
}

//----------------------------------------------------------------------------------------------------------------------
float ACustomLight::GetIntensity() const
{
	return CustomLight->GetLightComponent()->Intensity;
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
	CustomLight->SetLightFunctionMaterial(Material_Aggressive);
}

//----------------------------------------------------------------------------------------------------------------------
void ACustomLight::SetNormalMaterial() const
{
	CustomLight->SetLightFunctionMaterial(Material_Normal);
}

//----------------------------------------------------------------------------------------------------------------------
void ACustomLight::ChangeLightIntensity(float NewIntensity, bool bUseAsNewDefault)
{
	CustomLight->GetLightComponent()->SetIntensity(NewIntensity);

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
	CustomLight->GetLightComponent()->SetVisibility(false);
}

//----------------------------------------------------------------------------------------------------------------------
void ACustomLight::TurnOn() const
{
	CustomLight->GetLightComponent()->SetVisibility(true);
	CustomLight->GetLightComponent()->SetIntensity(FirstPointIntensity != 0 ? FirstPointIntensity : DefaultLightIntensity);
}
#pragma endregion


//----------------------------------------------------------------------------------------------------------------------
void ACustomLight::BeginPlay()
{
	Super::BeginPlay();
	
	if(bWillStartOff)
		CustomLight->GetLightComponent()->SetVisibility(false);
	
	FirstPointIntensity = CustomLight->GetLightComponent()->Intensity;
}