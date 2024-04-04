//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/SpectralWrittings.h"
#include "WrittingsDetector.generated.h"

UCLASS()
class THERITE_API AWrittingsDetector : public AActor
{
	GENERATED_BODY()
	
private:
	
	bool bwrittingDetected;
	bool bInteracionOn;

	ASpectralWrittings* currentWritting;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* TriggerDetector;

	UFUNCTION()
	void OnOverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnds(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetRadius(float newRadius);
	void SetLocation(FTransform newLocation);
	

public:
	AWrittingsDetector();
	virtual void Tick(float DeltaTime) override;

	void SetInteractionStatus(bool newStatus);
	void SetComponentSettings(float radius, FTransform transform);
};
