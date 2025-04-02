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
	~AAmbientSoundPlayer();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category="Settings")
	bool bIs2D;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	USoundBase* CueToSound;

	UAudioComponent* AudioComp;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void CreateAudio();
	
};