//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "TheRite/Characters/Alex.h"
#include "LockedDoor.generated.h"

class UTimelineComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteraction);

UCLASS()
class THERITE_API ALockedDoor : public AInteractor
{
	GENERATED_BODY()
	
private:
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
	
	AAlex* Player;
	
	bool bCanSoundItsLocked = true;
	
	UPROPERTY(EditAnywhere, Category= "States")
	bool bCanSound = true;
	
	UPROPERTY(EditAnywhere, Category= "States")
	bool bHasInteraction = true;
	
	bool bInteractionDone;

	float SoundTimer;

	UPROPERTY(EditAnywhere, Category= "CD sound")
	float SoundCD = 60.0f;
	

	//--------------Functions
	UFUNCTION()
	void ItsLocked();
	
	UFUNCTION()
	void OnAudioFinished();

	float CurveFloat;
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void TimeLineUpdate(float time);
	
	UFUNCTION()
	void TimelineFinished();
	//--------------TimeLine Compoenents
	
	FTimeline MyTimeline;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* MyFloatCurve;


public:	
	ALockedDoor();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "Interaction Delegate")
	FOnInteraction OnInteraction;
	
	virtual void Interaction() override;
};