//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
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
	bool IsLightOn();
	HouseZone GetLightZone();
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void AggresiveMatterial();
	
	UFUNCTION()
	void NormalMatterial();

	UFUNCTION()
	void TurnOff();
	
	UFUNCTION()
	void TurnOn();
	
private:
	float FirstPointIntensity;
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "If the Light starts off this will be the turning on intensity"))
	float DefaultLightIntensity;

	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "Set in whitch part of the house the light is"))
	HouseZone LightHouseZone;
	
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Category= "Lights")
	UPointLightComponent* PointLight;
	
	UPROPERTY()
	USphereComponent* Sphere;
	
	UPROPERTY(EditAnywhere, Category= "Materials")
	UMaterialInterface* NormalMaterial;
	
	UPROPERTY(EditAnywhere, Category= "Materials")
	UMaterialInterface* AggresiveMaterial;

};