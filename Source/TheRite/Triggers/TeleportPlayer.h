//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTeleportComplete);

UCLASS()
class THERITE_API ATeleportPlayer : public AActor
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ATeleportPlayer();
	
	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	FOnTeleportComplete OnTeleportComplete;
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bDestroyAfterUse;
	
	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = true))
	class ATargetPoint* TeleportLocation;

	UPROPERTY(EditAnywhere, Category = Doors)
	TArray<class ADoor*> ClosingDoors;
	
	UPROPERTY(EditAnywhere, Category= "Lights")
	TArray<class ALight*> TurnedOffLights;

	FTimerHandle TeleportTimer;
	FTimerDelegate TeleportDelegate;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};