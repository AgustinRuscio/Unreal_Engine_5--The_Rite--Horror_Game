//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	ACandle();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	UFUNCTION()
	void TurnOn() const;
	
	UFUNCTION()
	void TurnOff() const;

	void Appear() const;

	void Disappear() const;
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bTurnOffProximityDoOnce;

	UPROPERTY(EditAnywhere, Category="State")
	bool bStartsTurnedOn;

	UPROPERTY(EditAnywhere, Category="State")
	bool bProximityTurnedOff;

	UPROPERTY(EditAnywhere, Category="State")
	bool bWillTurnOff;
	
	UPROPERTY(EditAnywhere, Category="State")
	bool bWillSound;

	UPROPERTY(EditAnywhere, Category="State")
	bool bIsGuideCandle;

	UPROPERTY(EditAnywhere, Category="State")
	float TurnOffDistance;
	
	UPROPERTY(EditAnywhere, Category="Light")
	UPointLightComponent* PointLight;
	
	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* Plane;
	
	UPROPERTY(EditAnywhere, Category="Mesh")
	USoundBase* BlowCandleSound;
	
	UPROPERTY(EditAnywhere, Category="Mesh")
	UNiagaraComponent* SmokeParticles;

	class APawn* Player;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds);
};