//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RealWorldEndGameFlow.generated.h"

UCLASS()
class THERITE_API ARealWorldEndGameFlow : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ARealWorldEndGameFlow();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnyWhere, Category = Settings)
	FName NextLevelName;

	UPROPERTY(EditAnywhere, Category = Settings)
	USoundBase* SFX_Shoot;
	UPROPERTY(EditAnywhere, Category = Settings)
	USoundBase* SFX_Voice;

	UPROPERTY(EditAnywhere, Category = Settings)
	TArray<class ACustomLight*> CustomLights;

	UPROPERTY(EditAnywhere, Category = Settings)
	class AInteractor* EndGameInteractable;
	
	UPROPERTY(EditAnywhere, Category= "Sequence")
	class ULevelSequence* SequenceFade;

	UPROPERTY(EditAnywhere, Category= "Sequence")
	class ULevelSequence* SequenceShoot;

	class AAlex* Player;

	FTimerHandle TimerHandle_Voice;
	FTimerDelegate TimerDelegate_Voice;

	FTimerHandle TimerHandle_Shoot;
	FTimerDelegate TimerDelegate_Shoot;


private:
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	
	void PlaySequence();

	UFUNCTION()
	void OnSequenceFinished();

	void TurnLightsOff();

	UFUNCTION()
	void OnInteractableTriggered(class AInteractor* interactor);
};