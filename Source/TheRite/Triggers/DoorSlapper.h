//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorSlapper.generated.h"

class UBoxComponent;
class ADoor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlappedDoor);

UCLASS()
class THERITE_API ADoorSlapper : public AActor
{
	GENERATED_BODY()

	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ADoorSlapper();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnSlappedDoor OnSlappedDoor;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void Activate();
	void Deactivate();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category="Settings")
	bool bActive = true;
	UPROPERTY(EditAnywhere, Category="Settings")
	bool bLockDoor = true;
	
	UPROPERTY(EditAnywhere, Category = "Triggers", meta=(AllowPrivateAccess="true"))
	UBoxComponent* ClosingTrigger;
	
	UPROPERTY(EditAnywhere, Category= "Doors")
	TArray<ADoor*> DoorsToSlap;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void SlapDoor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};