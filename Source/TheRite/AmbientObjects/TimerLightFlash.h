//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerLightFlash.generated.h"

UCLASS()
class THERITE_API ATimerLightFlash : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ATimerLightFlash();

	UPROPERTY(EditAnywhere, Category = Components)
	class UBoxComponent* TriggerBox;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bFlipFlop;

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bLoop;

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bTurnOffOnPlayerOutside;

	UPROPERTY(EditAnywhere, Category = Settings)
	float Rate;

	UPROPERTY(EditAnywhere, Category = Settings)
	float LightIntensity;

	UPROPERTY(EditAnywhere, Category = Components)
	TArray<class ALight*> Lights;

	FTimerHandle TimerHandle;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void InterpLight();

	UFUNCTION()
	void OnPlayerInside(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerOutside(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};