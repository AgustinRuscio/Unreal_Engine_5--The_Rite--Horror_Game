//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
	AEmergencyLights();

//---------------- Functionality Methods
	void TurnOn() const;
	void TurnOff() const;
	
private:
//---------------- System Class Methods
	virtual void BeginPlay() override;
	
private:
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
	
};