//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TiffanyDestroy.generated.h"

class UBoxComponent;
class ALightsTheRite;
class ATiffany;

UCLASS()
class THERITE_API ATiffanyDestroy : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere, Category= "Near Light")
	ALightsTheRite*  NearLight;

	UPROPERTY(EditAnywhere, Category="Tiffany target")
	ATiffany* TiffanyToDestroy;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle FirstTimer;
	FTimerHandle SecondsTimer;

	void FirstTimeOver();
	void SecondTimeOver();
	
public:	
	ATiffanyDestroy();

};