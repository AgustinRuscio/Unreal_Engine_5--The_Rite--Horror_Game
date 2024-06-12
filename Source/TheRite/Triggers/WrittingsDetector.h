//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WrittingsDetector.generated.h"

class USphereComponent;
class ASpectralWrittings;

UCLASS()
class THERITE_API AWrittingsDetector : public AActor
{
	GENERATED_BODY()
	
public:
	AWrittingsDetector();
	virtual void Tick(float DeltaTime) override;

	void SetComponentSettings(float radius, FTransform transform);
	void SetInteractionStatus(bool newStatus);

private:
	void ChangeCurrentWrittingAlpha();
	void SetRadius(float newRadius);
	void SetLocation(FTransform newLocation);

	UFUNCTION()
	void OnOverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnds(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
private:
	bool bwrittingDetected;
	bool bInteracionOn;

	UPROPERTY(EditAnywhere)
	USphereComponent* TriggerDetector;
	
	ASpectralWrittings* currentWritting;
};