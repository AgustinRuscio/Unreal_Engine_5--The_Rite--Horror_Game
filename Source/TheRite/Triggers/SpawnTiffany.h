//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnTiffany.generated.h"

class ATargetPoint;
class ATiffany;
class APointLight;
class UBoxComponent;

UCLASS()
class THERITE_API ASpawnTiffany : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ASpawnTiffany();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;
	
	UPROPERTY(EditAnywhere, Category="Ambient")
	USoundBase* Sound;
	
	UPROPERTY(EditAnywhere, Category="Spawnning")
	ATargetPoint* SpawnPoint;

	UPROPERTY(EditAnywhere, Category="New states for Tiffany")
	TArray<ATargetPoint*> Waypoints;

	UPROPERTY(EditAnywhere, Category="Ambient")
	APointLight* Light;
	
	UPROPERTY(EditAnywhere, Category="New states for Tiffany")
	ATiffany* tif;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};