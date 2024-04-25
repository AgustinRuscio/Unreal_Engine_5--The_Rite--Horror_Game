//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Candle.generated.h"


class UNiagaraComponent;
class UPointLightComponent;

UCLASS()
class THERITE_API ACandle : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category="Light")
	UPointLightComponent* PointLight;
	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* Plane;

	UPROPERTY(EditAnywhere, Category="Mesh")
	UNiagaraComponent* SmokeParticles;
	
	UPROPERTY(EditAnywhere, Category="Mesh")
	USoundBase* BlowCandleSound;

	UPROPERTY(EditAnywhere, Category="State")
	bool bWillTurnOff;
	UPROPERTY(EditAnywhere, Category="State")
	bool bWillSound;

	UPROPERTY(EditAnywhere, Category="State")
	bool bIsGuideCandle;

	
public:	
	ACandle();
	
	UFUNCTION()
	void TurnOn();
	UFUNCTION()
	void TurnOff();
};