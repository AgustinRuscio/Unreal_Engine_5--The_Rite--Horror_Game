//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFlowDiaryLevelOtherWorld.generated.h"

class AInOrdenSelectionPuzzleFlow;
class ASpotLight;
class AAlex;
class ADoor;
class ATriggerVolume;
class ARectLight;
class ASkeletalMeshActor;
class ALightsTheRite;
class AInteractor;

UCLASS()
class THERITE_API AGameFlowDiaryLevelOtherWorld : public AActor
{
	GENERATED_BODY()
	
public:
	AGameFlowDiaryLevelOtherWorld();
//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
//---------------- Initialize Methods
	UFUNCTION()
	void BindTriggers();
	void BindMethods();
	void InitializeValues();
	
	UFUNCTION()
	void EndGame();

	UFUNCTION()
	void DinningRoomObjectEventGrab(AInteractor* a);
	
//---------------- Bind Colliders Methods
	UFUNCTION()
	void OnTriggerLivingRoomEventOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerKitchenEventOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnTriggerDinningRoomEventOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:	

private:
	bool bEventReadyDinningRoom;
	
//-------- Colliders
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_LivingRoomEvent;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_KitchenEvent;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_DinningEvent;
	
//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Ambient Audios")
	USoundBase* SFX_LastAudio;
	
	UPROPERTY(EditAnywhere, Category = "Ambient Audios")
	USoundBase* SFX_LightsOut;

//-------- Lights
	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ALightsTheRite*> Lights_AllLights;

	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ASpotLight*> Lights_SpotLightEndGame;
	
	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ASpotLight*> Lights_Altar;
	
	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ARectLight*> Lights_OtherLivingEvent;

//-------- Timers
	FTimerHandle Timer_LivingRoomEvent0;
	FTimerHandle Timer_LivingRoomEvent1;
	
	FTimerHandle Timer_KitchenEvent;
	
	FTimerHandle Timer_DinningRoomEvent;
	
//---------------------------------------- In game Objects
	
//-------- Meshes
	UPROPERTY(EditAnywhere, Category = "Meshes")
	TArray<ASkeletalMeshActor*> Skeletals_LivingRoomEvet;
	
	UPROPERTY(EditAnywhere, Category = "Meshes")
	TArray<ASkeletalMeshActor*> Skeletals_KitchenEvet;

	UPROPERTY(EditAnywhere, Category = "Meshes")
	TArray<ASkeletalMeshActor*> Skeletals_DinningRoomEvet;
	
//-------- Flows
	UPROPERTY(EditAnywhere, Category= "Settings")
	AInOrdenSelectionPuzzleFlow* InOrderPOuzzleController;

//-------- Doors
	UPROPERTY(EditAnywhere, Category= "Doors")
	ADoor* Doors_BathRoom;
	
	UPROPERTY(EditAnywhere, Category= "Doors")
	ADoor* Doors_BedRoom;
	
	UPROPERTY(EditAnywhere, Category= "Doors")
	ADoor* Doors_EndGame;

//-------- Interactors
	UPROPERTY(EditAnywhere, Category= "Interacors")
	AInteractor* InteractorEventDinningRoom;
	
//-------- Others
	AAlex* Player;
};