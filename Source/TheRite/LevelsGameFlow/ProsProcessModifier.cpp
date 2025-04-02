//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "ProsProcessModifier.h"
#include "Components/PostProcessComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

//----------------------------------------------------------------------------------------------------------------------
AProsProcessModifier::AProsProcessModifier()
{
 	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
void AProsProcessModifier::ModifyPostProcessValues(FName& parameterName, float value)
{
	DynamicMaterialPostProcess->SetScalarParameterValue(parameterName, value);
}

//----------------------------------------------------------------------------------------------------------------------
void AProsProcessModifier::BeginPlay()
{
	Super::BeginPlay();
	
	DynamicMaterialPostProcess = UMaterialInstanceDynamic::Create(PostProcesVHSdMaterial, this);
	PostProcessComponent->AddOrUpdateBlendable(DynamicMaterialPostProcess);
}