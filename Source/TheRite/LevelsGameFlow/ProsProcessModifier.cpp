//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ProsProcessModifier.h"
#include "Components/PostProcessComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AProsProcessModifier::AProsProcessModifier()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AProsProcessModifier::ModifyPostProcessValues(FName& parameterName, float value)
{
	DynamicMaterialPostProcess->SetScalarParameterValue(parameterName, value);
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AProsProcessModifier::BeginPlay()
{
	Super::BeginPlay();
	
	DynamicMaterialPostProcess = UMaterialInstanceDynamic::Create(PostProcesVHSdMaterial, this);
	PostProcessComponent->AddOrUpdateBlendable(DynamicMaterialPostProcess);
}