//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "SecondCorridorFlow.generated.h"

UCLASS()
class THERITE_API ASecondCorridorFlow : public AActor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ASecondCorridorFlow();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Settings")
	float m_TimeToTeleport;
	UPROPERTY(EditAnywhere, Category = "Settings")
	float m_FeedBackOffSetTime;

	UPROPERTY(EditAnywhere, Category = "Puzzles")
	class ALightsPuzzle* LightsPuzzle;

	UPROPERTY(EditAnywhere, Category = "Puzzles")
	class AInteractor* KeyLightsObject;

	UPROPERTY(EditAnywhere, Category = "Puzzles")
	class AInteractor* EmblemObject;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	TArray<class ACustomLight*> FeedbackLights;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	TArray<class AAmbientSoundPlayer*> FeedbackSounds;

	UPROPERTY(EditAnywhere, Category = "Settings")
	class ADoor* EmblemDoor;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	class ATargetPoint* TeleportTargetPoint;

	UPROPERTY(EditAnywhere, Category = FeedBack, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShake_Puzzle;

	class AAlex* player;

	FTimeline TimeLineFeedBack;

	UPROPERTY(EditAnywhere, Category = "TimeLine")
	UCurveFloat* CurveFloatMoveLightsKeyInteractor;

	FTimerHandle TimerHanldeTeleport;
	FTimerDelegate TimerDelegateTeleport;

	FTimerHandle   TimerHanldeFeedBackTimeOffset;
	FTimerDelegate TimerDelegateFeedBackTimeOffset;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnLightsPuzzleCompleted();
	void OnLightsPuzzleCompletedFeedBack();

	void ToggleLights(bool LightsOn);
	void ToggleSound(bool Active);

	void TeleportPlayer();

	UFUNCTION()
	void FeedBackTick(float DeltaSeconds);
	UFUNCTION()
	void FeedBackFinished(float DeltaSeconds);
};