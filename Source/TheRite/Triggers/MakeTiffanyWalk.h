#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Characters/Tiffany.h"
#include "MakeTiffanyWalk.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinished);

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


	UPROPERTY(EditAnywhere, Category="Tiffany")
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

	
	FTimeline FirstTimeLine;
	
	FTimeline SecondsTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* BothTimeLineCurve;
	
	UPROPERTY(EditAnywhere, Category = "Testing", meta=(ToolTip = "Set false when not testing"))
	bool bKeyReady;
	bool bReady;

	int8 DoOnce;

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
	void KeyOBtein(ATiffany* newTiff);
	
	virtual void Tick(float DeltaTime) override;

	FOnFinished OnFinished;
};

