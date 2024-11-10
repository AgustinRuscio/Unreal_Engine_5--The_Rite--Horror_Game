//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WalkerTiffany.generated.h"

UCLASS()
class THERITE_API AWalkerTiffany : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AWalkerTiffany();

	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

		
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	void Activate();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bReadyToWalk;

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bTiffanyCrawl;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	bool bUseLights;
	
	bool bDoOnce;

	UPROPERTY(EditAnywhere, Category = Settings)
	float AcceptanceDistance;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	class ATargetPoint* SpawnTargetPoint;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	class ATargetPoint* DesiredTargetPoint;

	UPROPERTY(EditAnywhere, Category = Settings)
	TArray<class ADoor*> OpeningDoors;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	TArray<class ALightsTheRite*> TheRiteLights;

	UPROPERTY(EditAnywhere, Category = Settings)
	TArray<class ASpotLight*> SpotLights;
	TArray<float> spotIntensities;
	
	class ATiffany* WalkerTiffany;
	
	UPROPERTY(EditAnywhere, Category = "Ligher")
	TSubclassOf<ATiffany> DetectorSubclass;
	
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

	void LightsOff();
	void LightsOn();
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};