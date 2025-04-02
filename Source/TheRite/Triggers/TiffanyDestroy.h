//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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

public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ATiffanyDestroy();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;
	
	FTimerHandle FirstTimer;
	FTimerHandle SecondsTimer;
	
	UPROPERTY(EditAnywhere, Category= "Near Light")
	ALightsTheRite*  NearLight;

	UPROPERTY(EditAnywhere, Category="Tiffany target")
	ATiffany* TiffanyToDestroy;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};