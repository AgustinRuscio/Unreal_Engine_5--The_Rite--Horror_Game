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

public:
	AMakeTiffanyWalk();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void KeyObtein(ATiffany* newTiff);

private:
//---------------- TimeLine Methods
	void BindTimeLines();
	
	UFUNCTION()
	void FirstTimeLineUpdate(float value);

	UFUNCTION()
	void FirstTimelineFinished();

	
	UFUNCTION()
	void SecondsTimeLineUpdate(float value);
	
	UFUNCTION()
	void SecondsTimelineFinished();

	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	FOnFinished OnFinishedEvent;
	FOnFinished OnStartEvent;
	
private:
	UPROPERTY(EditAnywhere, Category = "States")
	bool bKeyReady;
	
	UPROPERTY(EditAnywhere, Category = "States")
	bool bSoundAfterEvent;
	
	bool bReady;

	int8 DoOnce;
	int8 DoOnceTimeLine = 0;


	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	//-------- Audio
	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* SFXHeartBeat;
	
	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* SFXTiffanyNear;
	
	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* SFX_AfterEvent;

	//-------- Target Point
	UPROPERTY(EditAnywhere, Category="Target")
	ATargetPoint* MoveTarget;

	//-------- TimeLines
	FTimeline FirstTimeLine;
	FTimeline SecondsTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* BothTimeLineCurve;
	
	//-------- Lights
	UPROPERTY(EditAnywhere, Category="Lighst")
	TArray<ALightsTheRite*> OtherLights;
	TArray<ALightsTheRite*> Lights;
	
	UPROPERTY()
	ATiffany* Tiffany;
};