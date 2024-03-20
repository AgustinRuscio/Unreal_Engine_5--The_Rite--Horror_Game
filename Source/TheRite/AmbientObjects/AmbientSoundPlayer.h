#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "AmbientSoundPlayer.generated.h"


UCLASS()
class THERITE_API AAmbientSoundPlayer : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category="Settings")
	bool isTwoDimentional;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	USoundBase* CueToSound;

	UAudioComponent* AudioComponent;
	
	UFUNCTION()
	void CreateAudio();
	
protected:
	virtual void BeginPlay() override;

public:	
	AAmbientSoundPlayer();
};