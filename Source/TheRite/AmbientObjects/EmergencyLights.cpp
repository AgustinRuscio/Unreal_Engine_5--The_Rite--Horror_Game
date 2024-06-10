

#include "EmergencyLights.h"
#include "Components/RectLightComponent.h"

AEmergencyLights::AEmergencyLights()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Emergency light mesh");
	
	Light = CreateDefaultSubobject<URectLightComponent>("light");
	Light->SetupAttachment(Mesh);
}

void AEmergencyLights::BeginPlay()
{
	Super::BeginPlay();

	Material = Mesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	Mesh->SetMaterial(0, DynamicMaterial);

	if(bStartTurnedOff)
		TurnOff();
}

void AEmergencyLights::TurnOn()
{
	Light->SetIntensity(LightIntensity);
	DynamicMaterial->SetScalarParameterValue(TEXT("IntensityMultiplier"),EmmisiveMultiplierValue);
}

void AEmergencyLights::TurnOff()
{
	Light->SetIntensity(0);
	DynamicMaterial->SetScalarParameterValue(TEXT("IntensityMultiplier"),0);
}