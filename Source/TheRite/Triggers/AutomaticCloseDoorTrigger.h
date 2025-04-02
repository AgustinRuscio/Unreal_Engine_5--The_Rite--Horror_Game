//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "AutomaticCloseDoorTrigger.generated.h"

class ATriggerVolume;
class ADoor;


UCLASS()
class THERITE_API AAutomaticCloseDoorTrigger : public AActor
{
	GENERATED_BODY()

public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Contructor
	AAutomaticCloseDoorTrigger();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool playerInside;

	UPROPERTY(EditAnywhere, Category="Trigger")
	ATriggerVolume* RoomTrigger;

	FTimeline CloseDoorTimeLine;
	
	UPROPERTY(EditAnywhere, Category="Curves")
	UCurveFloat* CloseDoorCurve;
	
	UPROPERTY(EditAnywhere, Category="My door")
	ADoor* DoorToClose;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
//---------------- Timelines Methods
	void BindTimeLinesMethods();
	
	UFUNCTION()
	void OnTimerFinished();
	
//---------------- Collider Methods
	void BindTriggers();
	
	UFUNCTION()
	void CheckActorIn(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void CheckActorOut(AActor* OverlappedActor, AActor* OtherActor);
};