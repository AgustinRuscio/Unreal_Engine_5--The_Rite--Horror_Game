//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorScaryKnocking.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerActivated);

UCLASS()
class THERITE_API ADoorScaryKnocking : public AActor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ADoorScaryKnocking();

	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnTriggerActivated OnTriggerActivatedDelegate;
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	
	void Activate();
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bActive;

	bool bDoOnce;

	UPROPERTY(EditAnywhere, Category = FeedBack)
	TArray<class USoundBase*> SFX;
	
	UPROPERTY(EditAnywhere, Category = Objects)
	TArray<class ADoor*> Doors;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};