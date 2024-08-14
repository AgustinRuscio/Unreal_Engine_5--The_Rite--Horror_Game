//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WrittingsDetector.generated.h"

class USphereComponent;
class ASpectralWrittings;
class UFadeObjectComponent;
class IFader;

UCLASS()
class THERITE_API AWrittingsDetector : public AActor
{
	GENERATED_BODY()
	
public:
	AWrittingsDetector();

	void SetComponentSettings(float radius, FTransform transform);
	void SetInteractionStatus(bool newStatus);

private:
	virtual void Tick(float DeltaTime) override;
	
//---------------- Setter Methods
	void ChangeCurrentWritingAlpha();
	void SetRadius(float newRadius);
	void SetLocation(FTransform newLocation);

//---------------- Collision Methods
	UFUNCTION()
	void OnOverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnds(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
private:
	bool bwrittingDetected;
	bool bInteracionOn;

	UPROPERTY(EditAnywhere, Category="Settings")
	float Radius;

	UPROPERTY(EditAnywhere)
	USphereComponent* TriggerDetector;

	TArray<IFader*> OverlappedFadeObjects;
	
	//ASpectralWrittings* currentWritting;
};