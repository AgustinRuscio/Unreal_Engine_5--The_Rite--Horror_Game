//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmbientSoundPlayer.generated.h"


UCLASS()
class THERITE_API AAmbientSoundPlayer : public AActor
{
	GENERATED_BODY()

public:
	AAmbientSoundPlayer();
	~AAmbientSoundPlayer();
	
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	void CreateAudio();
	
private:
	UPROPERTY(EditAnywhere, Category="Settings")
	bool IsTwoDimentional;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	USoundBase* CueToSound;

	UAudioComponent* AudioComponent;
};