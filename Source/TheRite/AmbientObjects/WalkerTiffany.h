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
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bReadyToWalk;
	
	bool bDoOnce;

	UPROPERTY(EditAnywhere, Category = Settings)
	class ATargetPoint* SpawnTargetPoint;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	class ATargetPoint* DesiredTargetPoint;
	
	
	UPROPERTY(EditAnywhere, Category = Settings)
	class ATiffany* WalkerTiffany;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};