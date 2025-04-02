//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AWrittingsDetector();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void SetComponentSettings(float radius, FTransform transform);
	void SetInteractionStatus(bool newStatus);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bwrittingDetected;
	bool bInteracionOn;

	UPROPERTY(EditAnywhere, Category="Settings")
	float Radius;

	UPROPERTY(EditAnywhere)
	USphereComponent* TriggerDetector;

	TArray<IFader*> OverlappedFadeObjects;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
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
};