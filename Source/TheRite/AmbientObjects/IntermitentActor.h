//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IntermitentActor.generated.h"

UCLASS()
class THERITE_API AIntermitentActor : public AActor
{
	GENERATED_BODY()
	
public:
	AIntermitentActor();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void ActivateIntermitent();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bShouldTurnLightsOffBefore;

	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bShouldTurnLightsOnAfter;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float IntermitentTimeOn;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float IntermitentTimeOff;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TArray<AActor*> IntermitentActors;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TArray<class ALightsTheRite*> Lights;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TArray<class ACustomLight*> CustomLights;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TArray<USoundBase*> SFX;

	FTimerHandle IntermitentTimerOn;
	FTimerDelegate IntermitentDelegateOn;

	FTimerHandle IntermitentTimerOff;
	FTimerDelegate IntermitentDelegateOff;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	void ToggleLights(bool active);
	void ToggleActorsVisibility(bool hidden);
};