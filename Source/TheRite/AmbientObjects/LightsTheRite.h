#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Actor.h"
#include "LightsTheRite.generated.h"

UCLASS()
class THERITE_API ALightsTheRite : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	USphereComponent* Sphere;
	
	UPROPERTY(EditAnywhere, Category= "Lights")
	USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere, Category= "Lights")
	UPointLightComponent* PointLight;

	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* Mesh;


	float FirstStopIntensity;
	float FirstPointIntensity;

	UPROPERTY(EditAnywhere, Category= "Materials")
	UMaterialInterface* NormalMaterial;
	
	UPROPERTY(EditAnywhere, Category= "Materials")
	UMaterialInterface* AggresiveMaterial;
	
protected:
	virtual void BeginPlay() override;

public:
	ALightsTheRite();

	UFUNCTION()
	void AggresiveMatterial();
	
	UFUNCTION()
	void NormalMatterial();

	UFUNCTION()
	void TurnOff();
	UFUNCTION()
	void TurnOffSpotLight();
	
	UFUNCTION()
	void TurnOn();
};