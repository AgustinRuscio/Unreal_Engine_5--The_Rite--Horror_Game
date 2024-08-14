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
	
	
private:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void CreateAudio();
	
private:
	UPROPERTY(EditAnywhere, Category="Settings")
	bool bIs2D;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	USoundBase* CueToSound;

	UAudioComponent* AudioComp;
};