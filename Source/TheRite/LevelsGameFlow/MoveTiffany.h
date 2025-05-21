//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Engine/SpotLight.h"
#include "GameFramework/Actor.h"
#include "TheRite/Characters/Alex.h"
#include "MoveTiffany.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveFinished);

class ATiffany;
class UBoxComponent;
class ALightsTheRite;
class AAlex;
class ATargetPoint;

UCLASS()
class THERITE_API AMoveTiffany : public AActor
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AMoveTiffany();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnMoveFinished OnFinishedEvent;
	FOnMoveStart OnStartEvent;
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void AssignTiffany(ATiffany* newTiff);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bActionReady;
	int8 DoOnce;

	UPROPERTY(EditAnywhere, Category="Settings")
	float SpotLightIntensity = .3f;
	
	//-------- Colliders
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	//-------- Audio
	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* SFXHeartBeat;

	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* SFXTiffanyNear;
	
	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* SuddenSound;

	//-------- Target point
	UPROPERTY(EditAnywhere, Category="TargetPoint")
	ATargetPoint* Target;

	//-------- Timelines
	FTimerHandle FirstTurnLightsOff;
	FTimerHandle FirstTurnLightsOn;
	FTimerHandle FirstWait;
	FTimerHandle SecondWait;
	FTimerHandle SecondTurnLightsOff;
	FTimerHandle SecondTurnLightsOn;
	
	//-------- Lights
	UPROPERTY(EditAnywhere, Category="Ambient")
	TArray<class ACustomLight*> CustomOtherLights;


	UPROPERTY(EditAnywhere, Category="Ambient")
	class ASpotLight* InGameSportLight;

	ATiffany* Tiffany;
	AAlex* Player;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	
//---------------- Timelines Methods
	UFUNCTION()
	void FirstTurnOn();
	
	UFUNCTION()
	void SecondTurnOff();
	
	UFUNCTION()
	void SecondTurnOn();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};