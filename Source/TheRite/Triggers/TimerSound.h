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

	void Activate();
	void Deactivate();

private:
	USoundBase* CurrentAudio() const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void ChangeCoolDown();
	void SpawnAudio();
	
private:
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
};