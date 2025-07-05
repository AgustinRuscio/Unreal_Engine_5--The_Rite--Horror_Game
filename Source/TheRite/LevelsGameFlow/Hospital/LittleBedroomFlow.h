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
	bool bDoOnce;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	float m_TimeToTeleport;
	UPROPERTY(EditAnywhere, Category = "Settings")
	float m_TimeToDestroy;

	UPROPERTY(EditAnywhere, Category = "Settings")
	class AInteractor* TeleportInteractor;

	UPROPERTY(EditAnywhere, Category = "Settings")
	class ATargetPoint* TeleportTargetPoint;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	TArray<class ACustomLight*> FeedbackLights;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	TArray<class ACandle*> FeedbackCandles;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	TArray<class AAmbientSound*> FeedbackSounds;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	TArray<class USoundBase*> FeedbackSoundsDestroyTiffany;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	class ATriggerVolume* TriggerBox;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	TArray<AActor*> ActorsToDestroy;

	
	UPROPERTY(EditAnywhere, Category = FeedBack, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShake_Puzzle;


	class AAlex* Player;

	FTimerHandle TimerHanldeTeleport;
	FTimerDelegate TimerDelegateTeleport;


	FTimerHandle TimerHanldeDestroyTiffany;
	FTimerDelegate TimerDelegateDestroyTiffany;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTeleportBegin(class AInteractor* interactor);
	
	void TeleportPlayer();

	void PerfromFeedBack();
	void StopFeedBack();

	void DestroyTiffany();
	void LightToggle(bool active);

	void PlayHaptipcFeedBack();

	UFUNCTION()
    void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};