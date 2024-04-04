//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Door.h"
#include "AutomaticCloseDoorTrigger.generated.h"

UCLASS()
class THERITE_API AAutomaticCloseDoorTrigger : public AActor
{
	GENERATED_BODY()


private:

	UPROPERTY(EditAnywhere, Category="My door")
	ADoor* DoorToClose;

	UPROPERTY(EditAnywhere, Category="Trigger")
	ATriggerVolume* RoomTrigger;

	bool playerInside;

	FTimeline CloseDoorTimeLine;
	
	UPROPERTY(EditAnywhere, Category="Curves")
	UCurveFloat* CloseDoorCurve;
	
protected:
	virtual void BeginPlay() override;

public:	
	AAutomaticCloseDoorTrigger();
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void CheckActorIn(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void CheckActorOut(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnTimerFinished();
};
