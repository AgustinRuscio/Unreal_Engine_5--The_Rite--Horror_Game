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
	
public:
	ATimerSound();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	USoundBase* CurrentAudio() const;
	void ChangeCoolDown();
	void SpawnAudio();
	
private:	
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
};