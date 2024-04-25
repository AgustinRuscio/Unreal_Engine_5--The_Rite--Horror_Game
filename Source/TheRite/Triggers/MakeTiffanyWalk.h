//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "MakeTiffanyWalk.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStart);

class ATiffany;
class ALightsTheRite;
class ATargetPoint;
class UBoxComponent;

UCLASS()
class THERITE_API AMakeTiffanyWalk : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY()
	ATiffany* Tiffany;

	UPROPERTY(EditAnywhere, Category="Tiffany")
	ATargetPoint* Target;

	UPROPERTY()
	TArray<ALightsTheRite*> Lights;
	
	UPROPERTY(EditAnywhere, Category="Ambient")
	TArray<ALightsTheRite*> OtherLights;
	
	UPROPERTY(EditAnywhere, Category="SFX")
	USoundBase* SFXHeartBeat;
	
	UPROPERTY(EditAnywhere, Category="SFX")
	USoundBase* SFXTiffanyNear;
	
	UPROPERTY(EditAnywhere, Category="SFX")
	USoundBase* SFX_AfterEvent;

	
	FTimeline FirstTimeLine;
	
	FTimeline SecondsTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* BothTimeLineCurve;
	
	UPROPERTY(EditAnywhere, Category = "States")
	bool bKeyReady;
	bool bReady;
	
	UPROPERTY(EditAnywhere, Category = "States")
	bool bSoundAfterEvent;

	int8 DoOnce;
	int8 DoOnceTimeLine = 0;

	UFUNCTION()
	void FirstTimeLineUpdate(float value);

	UFUNCTION()
	void FirstTimelineFinished();

	
	UFUNCTION()
	void SecondsTimeLineUpdate(float value);
	
	UFUNCTION()
	void SecondsTimelineFinished();

void BindTimeLines();

protected:
	virtual void BeginPlay() override;
	
public:	
	AMakeTiffanyWalk();

	UFUNCTION()
	void KeyObtein(ATiffany* newTiff);
	
	virtual void Tick(float DeltaTime) override;

	FOnFinished OnFinishedEvent;
	FOnFinished OnStartEvent;
};

