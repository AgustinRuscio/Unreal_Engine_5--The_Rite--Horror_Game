//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "EmergencyLights.h"
#include "Components/RectLightComponent.h"
#include "Components/PointLightComponent.h"

//*****************************Public******************************************
//******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AEmergencyLights::AEmergencyLights()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Emergency light mesh");
	
	RectLight = CreateDefaultSubobject<URectLightComponent>("light");
	RectLight->SetupAttachment(Mesh);

	PointLight = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	PointLight->SetupAttachment(Mesh);
}

//----------------------------------------------------------------------------------------------------------------------
void AEmergencyLights::TurnOn() const
{
	RectLight->SetIntensity(LightIntensity);
	PointLight->SetIntensity(LightIntensityPointLight);

	DynamicMaterial->SetScalarParameterValue(TEXT("IntensityMultiplier"),EmmisiveMultiplierValue);
}

//----------------------------------------------------------------------------------------------------------------------
void AEmergencyLights::TurnOff() const
{
	RectLight->SetIntensity(0);
	PointLight->SetIntensity(0);

	DynamicMaterial->SetScalarParameterValue(TEXT("IntensityMultiplier"),0);
}

//*****************************Private******************************************
//******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AEmergencyLights::BeginPlay()
{
	Super::BeginPlay();

	Material = Mesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	Mesh->SetMaterial(0, DynamicMaterial);

	if(bStartTurnedOff)
		TurnOff();
}