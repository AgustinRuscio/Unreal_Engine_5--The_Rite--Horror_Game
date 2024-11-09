//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BackCorridorFlow.generated.h"

UCLASS()
class THERITE_API ABackCorridorFlow : public AActor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ABackCorridorFlow();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	void ActivateZone() const;
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Settings)
	float TimeToMovePlayerOnEndPuzzle;
	
	UPROPERTY(EditAnywhere, Category = InitialDoors)
	TArray<class ADoor*> InitialDoors;
	
	UPROPERTY(EditAnywhere, Category = InitialDoors)
	TArray<class ADoor*> EndDoors; 

	UPROPERTY(EditAnywhere, Category = InitialDoors)
	class ATeleportPlayer* InitialTeleportPlayer;

	UPROPERTY(EditAnywhere, Category = InitialDoors)
	TArray<AActor*> ActorsToDestroyOnPuzzleBegin;

	UPROPERTY(EditAnywhere, Category = Puzzle)
	class ALeverPuzzle* LeverPuzzle;

	UPROPERTY(EditAnywhere, Category = Puzzle)
	class ATargetPoint* TargetPoint_EndPuzzle;
	
	UPROPERTY(EditAnywhere, Category = FeedBack, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShake_Puzzle;

	UPROPERTY(EditAnywhere, Category = FeedBack, meta=(AllowPrivateAccess = "true"))
	TArray<class ALightsTheRite*> AllLights;
	
	UPROPERTY(EditAnywhere, Category = FeedBack, meta=(AllowPrivateAccess = "true"))
	class USoundBase* SFX_PuzzleEnd;
	UPROPERTY(EditAnywhere, Category = FeedBack, meta=(AllowPrivateAccess = "true"))
	class USoundBase* SFX_PuzzleEnd_LightsOff;
	
	class AAlex* PLayer;


	FTimerHandle TimerHandle_PuzzleEnd;
	FTimerDelegate TimerDelegate_PuzzleEnd;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void OnPuzzleStarted();

	UFUNCTION()
	void OnPuzzleEnd();
};