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
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	void SlapDoor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, Category = "Triggers", meta=(AllowPrivateAccess="true"))
	UBoxComponent* ClosingTrigger;
	
	UPROPERTY(EditAnywhere, Category= "Doors")
	TArray<ADoor*> DoorsToSlap;
};