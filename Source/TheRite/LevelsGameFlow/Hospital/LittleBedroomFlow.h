//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LittleBedroomFlow.generated.h"

UCLASS()
class THERITE_API ALittleBedroomFlow : public AActor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ALittleBedroomFlow();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Settings")
	float m_TimeToTeleport;

	UPROPERTY(EditAnywhere, Category = "Settings")
	class AInteractor* TeleportInteractor;

	UPROPERTY(EditAnywhere, Category = "Settings")
	class ATargetPoint* TeleportTargetPoint;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	TArray<class ACustomLight*> FeedbackLights;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	TArray<class AAmbientSoundPlayer*> FeedbackSounds;

	class AAlex* Player;

	FTimerHandle TimerHanldeTeleport;
	FTimerDelegate TimerDelegateTeleport;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTeleportBegin(class AInteractor* interactor);
	
	void TeleportPlayer();

	void PerfromFeedBack();
	void StopFeedBack();
};