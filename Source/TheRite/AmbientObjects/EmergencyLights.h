//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmergencyLights.generated.h"

class URectLightComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;

UCLASS()
class THERITE_API AEmergencyLights : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	AEmergencyLights();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void TurnOn() const;
	void TurnOff() const;
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
//-------- Settings
	UPROPERTY(EditAnywhere, Category="Settings")
	bool bStartTurnedOff;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	float EmmisiveMultiplierValue;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	float LightIntensity;
	
//-------- Mesh
	UPROPERTY(EditAnywhere, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	
//-------- Material
	UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynamicMaterial;
	
//-------- Lights
	UPROPERTY(EditAnywhere, Category="Lights")
	URectLightComponent* Light;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
};