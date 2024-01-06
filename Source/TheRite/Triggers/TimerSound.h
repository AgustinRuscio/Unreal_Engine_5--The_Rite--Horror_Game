#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerSound.generated.h"

UCLASS()
class THERITE_API ATimerSound : public AActor
{
	GENERATED_BODY()
	
private:	

	float Timer;

	UPROPERTY(EditAnywhere, Category= "Sound Cd")
	float CooldDown;

	UPROPERTY(EditAnywhere, Category= "Sound")
	USoundBase* Sound;


public:	
	ATimerSound();
	virtual void Tick(float DeltaTime) override;
};
