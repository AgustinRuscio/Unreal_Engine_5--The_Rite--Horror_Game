//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "LockedDoor.generated.h"

class UTimelineComponent;
class UBoxComponent;
class AAlex;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteraction);

UCLASS()
class THERITE_API ALockedDoor : public AInteractor
{
	GENERATED_BODY()

public:
	ALockedDoor();
	
	virtual void Interaction() override;

private:
	//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
//---------------- FeedBack Methods
	UFUNCTION()
	void ItsLocked();
	
	UFUNCTION()
	void OnAudioFinished();

//---------------- TimeLine Methods
	void BindTimelines();
	
	UFUNCTION()
	void TimeLineUpdate(float time);
	
	UFUNCTION()
	void TimelineFinished();

public:	
	UPROPERTY(BlueprintAssignable, Category = "Interaction Delegate")
	FOnInteraction OnInteraction;
	
private:
	bool bCanSoundItsLocked = true;
	
	UPROPERTY(EditAnywhere, Category= "States")
	bool bCanSound = true;
	
	UPROPERTY(EditAnywhere, Category= "States")
	bool bHasInteraction = true;
	
	bool bInteractionDone;
	
	float SoundTimer;

	UPROPERTY(EditAnywhere, Category= "CD sound")
	float SoundCD = 60.0f;
	
	float CurveFloat;
	
	//--------------Mesh Compoenents
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* DoorItself;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Latch;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UBoxComponent* BoxCollision;
	
	//--------------Audio Compoenents
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* DoorLockedSFX;
	
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* AudioInteractionDone;

	UAudioComponent* tempAudioComponent;
	
	FTimeline MyTimeline;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* MyFloatCurve;
	
	AAlex* Player;
};