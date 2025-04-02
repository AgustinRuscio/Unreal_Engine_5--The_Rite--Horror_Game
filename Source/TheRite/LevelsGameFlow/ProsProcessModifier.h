//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AProsProcessModifier();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void ModifyPostProcessValues(FName& parameterName, float value);
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Post process event")
	UMaterialInterface* PostProcesVHSdMaterial;
	UMaterialInstanceDynamic* DynamicMaterialPostProcess;

	UPROPERTY(EditAnywhere, Category = "Post process event")
	UPostProcessComponent* PostProcessComponent;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
};