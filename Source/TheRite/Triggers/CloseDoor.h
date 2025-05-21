//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	ACloseDoor();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Closing Door")
	bool bWillLockTheDoor = false;
	
	UPROPERTY(EditAnywhere, Category = "Ambient")
	bool bAggresiveLight;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;
	
	UPROPERTY(EditAnywhere, Category = "Ambient")
	USoundBase* SFXLightBReak;
	
	//-------- Lights
	UPROPERTY(EditAnywhere, Category = "Ambient")
	TArray<ALightsTheRite*> Lights;

	UPROPERTY(EditAnywhere, Category = "Ambient")
	TArray<class ACustomLight*> CustomLights;
	
	UPROPERTY(EditAnywhere, Category = "Closing Door")
	ADoor* Door;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};