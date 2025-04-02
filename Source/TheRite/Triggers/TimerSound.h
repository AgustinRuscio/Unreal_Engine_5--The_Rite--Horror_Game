//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerSound.generated.h"

class AAlex;

UCLASS()
class THERITE_API ATimerSound : public AActor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ATimerSound();


	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void Activate();
	void Deactivate();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = Settings)
	bool bIsActive = true;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	float MinCoolDown;
	UPROPERTY(EditAnywhere, Category= "Settings")
	float MaxCooldDown;

	float Timer;
	float CooldDown;
	
	UPROPERTY(EditAnywhere, Category= "Audio")
	TArray<USoundBase*> PosibleSounds;
	
	UPROPERTY(EditAnywhere, Category= "Audio")
	USoundAttenuation* FxAttenuation;
	
	AAlex* Player;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	USoundBase* CurrentAudio() const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void ChangeCoolDown();
	void SpawnAudio();
};