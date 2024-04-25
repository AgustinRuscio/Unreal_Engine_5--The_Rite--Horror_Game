//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CloseDoor.generated.h"

class UBoxComponent;
class ALightsTheRite;
class ADoor;

UCLASS()
class THERITE_API ACloseDoor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, Category = "Closing Door")
	ADoor* Door;
	
	UPROPERTY(EditAnywhere, Category = "Closing Door")
	bool bWillLockTheDoor = false;

	UPROPERTY(EditAnywhere, Category = "Ambient")
	TArray<ALightsTheRite*> Lights;
	
	UPROPERTY(EditAnywhere, Category = "Ambient")
	ALightsTheRite* DestroyableLight;

	UPROPERTY(EditAnywhere, Category = "Ambient")
	USoundBase* SFXLightBReak;
	
	UPROPERTY(EditAnywhere, Category = "Ambient")
	bool bAggresiveLight;

public:	
	ACloseDoor();

};