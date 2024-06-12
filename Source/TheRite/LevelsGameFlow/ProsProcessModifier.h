//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProsProcessModifier.generated.h"

class UPostProcessComponent;

UCLASS()
class THERITE_API AProsProcessModifier : public AActor
{
	GENERATED_BODY()

public:	
	AProsProcessModifier();
	virtual void BeginPlay() override;

	void ModifyPostProcessValues(FName& parameterName, float value);
	
private:	
	UPROPERTY(EditAnywhere, Category = "Post process event")
	UMaterialInterface* PostProcesVHSdMaterial;
	UMaterialInstanceDynamic* DynamicMaterialPostProcess;

	UPROPERTY(EditAnywhere, Category = "Post process event")
	UPostProcessComponent* PostProcessComponent;
};