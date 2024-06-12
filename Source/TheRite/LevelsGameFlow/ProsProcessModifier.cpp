//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ProsProcessModifier.h"
#include "Components/PostProcessComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

AProsProcessModifier::AProsProcessModifier()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void AProsProcessModifier::BeginPlay()
{
	Super::BeginPlay();
	
	DynamicMaterialPostProcess = UMaterialInstanceDynamic::Create(PostProcesVHSdMaterial, this);
	PostProcessComponent->AddOrUpdateBlendable(DynamicMaterialPostProcess);
}

void AProsProcessModifier::ModifyPostProcessValues(FName& parameterName, float value)
{
	DynamicMaterialPostProcess->SetScalarParameterValue(parameterName, value);
}