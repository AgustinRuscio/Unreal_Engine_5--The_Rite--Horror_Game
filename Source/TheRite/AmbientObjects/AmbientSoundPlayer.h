//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmbientSoundPlayer.generated.h"


UCLASS()
class THERITE_API AAmbientSoundPlayer : public AActor
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	AAmbientSoundPlayer();
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void StartAudioManually(bool loop, bool global);
	void StopAudios();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category="Settings")
	bool bCreateOnBeginPlay;

	UPROPERTY(EditAnywhere, Category="Settings")
	bool bLoop;;

	UPROPERTY(EditAnywhere, Category="Settings")
	bool bIs2D;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	USoundBase* CueToSound;

	UAudioComponent* AudioComp;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void CreateAudio();
};