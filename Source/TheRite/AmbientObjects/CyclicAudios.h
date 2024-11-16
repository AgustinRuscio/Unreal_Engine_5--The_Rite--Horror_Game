//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CyclicAudios.generated.h"

UCLASS()
class THERITE_API ACyclicAudios : public AActor
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ACyclicAudios();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void Activate();

	void PlayNextAudio();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bStartEnable;
	bool bSoundPlaying;
	
	int8 AudioPlayedIndex;

	UPROPERTY(EditAnywhere, Category = Settings)
	float OffSetTimeToNextAudio;
	float TimeToNextAudio;
	float TimeToNextAudioColdDown;

	UPROPERTY(EditAnywhere, Category = Audios)
	TArray<class USoundBase*> ClueSounds;

	UPROPERTY(EditAnywhere, Category = Audios)
	class USoundAttenuation* Attenuation;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};