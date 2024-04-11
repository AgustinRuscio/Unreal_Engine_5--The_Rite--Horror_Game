//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"

#include "Components/PostProcessComponent.h"
#include "GameFramework/Actor.h"
#include "ProsProcessModifier.generated.h"

UCLASS()
class THERITE_API AProsProcessModifier : public AActor
{
	GENERATED_BODY()
	
private:	

	UPROPERTY(EditAnywhere, Category = "Post process event")
	UMaterialInterface* PostProcesVHSdMaterial;
	UMaterialInstanceDynamic* DynamicMaterialPostProcess;

	UPROPERTY(EditAnywhere, Category = "Post process event")
	UPostProcessComponent* PostProcessComponent;
protected:
	virtual void BeginPlay() override;

public:	
	AProsProcessModifier();

	void ModifyPostProcessValues(FName& parameterName, float value);
};
