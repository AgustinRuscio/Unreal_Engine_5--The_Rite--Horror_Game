//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "TheRite/AmbientObjects/Candle.h"
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

private:
	virtual void BeginPlay() override;
	
//---------------- Initialize Methods
	UFUNCTION()
	void BindTriggers();
	void BindMethods();
	void InitializeValues();
	
	UFUNCTION()
	void EndGame();

	UFUNCTION()
	void DinningRoomObjectEventGrab(AInteractor* a);
	
//---------------- Colliders Methods
	UFUNCTION()
	void OnTriggerLivingRoomEventOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerKitchenEventOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnTriggerDinningRoomEventOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerEndGamePassOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:	

private:
	bool bEventReadyDinningRoom;
	bool bLivingRoomEventDone = false;
	bool bKitchenEventDone = false;
	bool bDinningRoomEventDone = false;
	bool bEndGamePassDone = false;
	
//-------- Colliders
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_LivingRoomEvent;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_KitchenEvent;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_DinningEvent;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_EndGamePass;
	
//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_TiffanyNearEvent;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_SuddenEvent;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_LastAudio;
	
	UPROPERTY(EditAnywhere, Category = "Ambient Audios")
	USoundBase* SFX_LightsOut;

//-------- Lights
	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ALightsTheRite*> Lights_AllLights;

	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ASpotLight*> Lights_DinningEventLights;
	
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

	UPROPERTY(EditAnywhere, Category= "Triggers")
	TArray<AStaticMeshActor*> EndGameWall;
	
//-------- Flows
	UPROPERTY(EditAnywhere, Category= "Settings")
	AInOrdenSelectionPuzzleFlow* InOrderPOuzzleController;

	
	UPROPERTY(EditAnywhere, Category="Candles")
	TArray<ACandle*> Candles_EndGame;
	
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