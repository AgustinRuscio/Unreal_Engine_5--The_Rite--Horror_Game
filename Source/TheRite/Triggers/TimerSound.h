//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerSound.generated.h"

class AAlex;

UCLASS()
class THERITE_API ATimerSound : public AActor
{
	GENERATED_BODY()
	
private:	

	float Timer;

	float CooldDown;
	
	UPROPERTY(EditAnywhere, Category= "Sound Cd")
	float MinCoolDown;
	UPROPERTY(EditAnywhere, Category= "Sound Cd")
	float MaxCooldDown;


	AAlex* Player;
	
	UPROPERTY(EditAnywhere, Category= "Sound")
	TArray<USoundBase*> PosibleSounds;
	UPROPERTY(EditAnywhere, Category= "Sound")
	USoundAttenuation* FxAttenuation;
	
	USoundBase* CurrentAudio() const;
	void ChangeCoolDown();
	
public:
	ATimerSound();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};