//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
	AAutomaticCloseDoorTrigger();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	void BindTriggers();
	
//---------------- Timelines Methods
	void BinddTimeLinesMethods();
	
	UFUNCTION()
	void OnTimerFinished();
	
//---------------- Collider Methods
	UFUNCTION()
	void CheckActorIn(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void CheckActorOut(AActor* OverlappedActor, AActor* OtherActor);
	
private:
	bool playerInside;

	UPROPERTY(EditAnywhere, Category="Trigger")
	ATriggerVolume* RoomTrigger;

	FTimeline CloseDoorTimeLine;
	
	UPROPERTY(EditAnywhere, Category="Curves")
	UCurveFloat* CloseDoorCurve;
	
	UPROPERTY(EditAnywhere, Category="My door")
	ADoor* DoorToClose;
};