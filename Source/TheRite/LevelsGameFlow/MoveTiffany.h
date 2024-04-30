//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
class ATargetPoint;

UCLASS()
class THERITE_API AMoveTiffany : public AActor
{
	GENERATED_BODY()
	
private:

	bool bActionReady;
	int8 DoOnce;
	
	ATiffany* Tiffany;

	UPROPERTY(EditAnywhere, Category="Tiffany")
	ATargetPoint* Target;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	FTimerHandle FirstTurnLightsOff;
	FTimerHandle FirstTurnLightsOn;
	FTimerHandle FirstWait;
	FTimerHandle SecondWait;
	FTimerHandle SecondTurnLightsOff;
	FTimerHandle SecondTurnLightsOn;
	
	UPROPERTY(EditAnywhere, Category="Tiffany")
	USoundBase* SFXHeartBeat;

	UPROPERTY(EditAnywhere, Category="Tiffany")
	USoundBase* SFXTiffanyNear;
	
	UPROPERTY(EditAnywhere, Category="Ambient")
	TArray<ALightsTheRite*> OtherLights;

	UPROPERTY(EditAnywhere, Category="Ambient")
	ASpotLight* InGameSportLight;

	AAlex* Player;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void FirstTurnOn();
	UFUNCTION()
	void SecondTurnOff();
	UFUNCTION()
	void SecondTurnOn();

public:
	virtual void BeginPlay() override;
	AMoveTiffany();

	void AsignTiffany(ATiffany* newTiff);

	FOnMoveFinished OnFinishedEvent;
	FOnMoveStart OnStartEvent;
};