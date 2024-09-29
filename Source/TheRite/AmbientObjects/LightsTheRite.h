//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheRite/EnumsContainer.h"
#include "LightsTheRite.generated.h"

class UPointLightComponent;
class USphereComponent;

UCLASS()
class THERITE_API ALightsTheRite : public AActor
{
	GENERATED_BODY()

public:
	ALightsTheRite();
	bool IsLightOn() const;
	float GetIntensity() const;
	HouseZone GetLightZone() const;
	HospitalZone GetHospitalZone() const;
	
	
	UFUNCTION()
	void SetAggressiveMaterial() const;
	
	UFUNCTION()
	void SetNormalMaterial() const;
	
	void ChangeLightIntensity(float NewIntensity, bool bUseAsNewDefault);
	
	UFUNCTION()
	void TurnOff() const;
	
	UFUNCTION()
	void TurnOn() const;

private:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "If the Light starts off"))
	bool bWillStartOff;
	
	float FirstPointIntensity;
	
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "If the Light starts off this will be the turning on intensity"))
	float DefaultLightIntensity;

	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "Set in whitch part of the house the light is"))
	HouseZone LightHouseZone;

	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "Set in whitch part of the house the light is"))
	HospitalZone HospitalZone;
	
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Category= "Lights")
	class UPointLightComponent* PointLight;

	UPROPERTY(EditAnywhere, Category = "SFX", meta=(AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComponent;
	
	UPROPERTY()
	USphereComponent* Sphere;
	
	UPROPERTY(EditAnywhere, Category= "Materials")
	UMaterialInterface* Material_Normal;
	
	UPROPERTY(EditAnywhere, Category= "Materials")
	UMaterialInterface* Material_Aggressive;
};