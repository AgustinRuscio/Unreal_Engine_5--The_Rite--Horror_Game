//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorSlapper.generated.h"

class UBoxComponent;
class ADoor;

UCLASS()
class THERITE_API ADoorSlapper : public AActor
{
	GENERATED_BODY()

	
public:	
	ADoorSlapper();

	void Activate();
	void Deactivate();
	
private:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void SlapDoor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, Category="Settings")
	bool bActive = true;
	
	UPROPERTY(EditAnywhere, Category = "Triggers", meta=(AllowPrivateAccess="true"))
	UBoxComponent* ClosingTrigger;
	
	UPROPERTY(EditAnywhere, Category= "Doors")
	TArray<ADoor*> DoorsToSlap;
};