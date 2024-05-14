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

UCLASS()
class THERITE_API AGameFlowDiaryLevelOtherWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameFlowDiaryLevelOtherWorld();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void EndGame();

	UFUNCTION()
	void BindTriggers();
	void BindMethods();
	void InitializeValues();

	UFUNCTION()
	void OnTriggerLivingRoomEventOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerKitchenEventOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:	

private:
	//-------- Colliders
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_LivingRoomEvent;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_KitchenEvent;
	
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
	FTimerHandle Timer_LivingRoomEvent;
	FTimerHandle Timer_KitchenEvent;
	
	//-------- In game Meshes
	
	UPROPERTY(EditAnywhere, Category = "Meshes")
	TArray<ASkeletalMeshActor*> Skeletals_LivingRoomEvet;
	UPROPERTY(EditAnywhere, Category = "Meshes")
	TArray<ASkeletalMeshActor*> Skeletals_KitchenEvet;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	AInOrdenSelectionPuzzleFlow* InOrderPOuzzleController;

	UPROPERTY(EditAnywhere, Category= "Doors")
	
	ADoor* Doors_BathRoom;
	UPROPERTY(EditAnywhere, Category= "Doors")
	
	ADoor* Doors_BedRoom;
	UPROPERTY(EditAnywhere, Category= "Doors")
	ADoor* Doors_EndGame;

	AAlex* Player;
};
