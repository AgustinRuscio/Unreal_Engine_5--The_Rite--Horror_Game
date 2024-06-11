//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFlowPacifierLevel.generated.h"

class AInteractor;
class ARectLight;
class ATriggerVolume;
class ALightsTheRite;
class ALightSwitch;
class ALadder;
class ADoor;
class AAlex;
class ABasePlayerSettingsSetter;
class ACandle;
class AEmergencyLights;
class ABlockingVolume;
class AFetusPuzzle;
class ASkeletalMeshActor;
class ATargetPoint;
class AAmbientSound;

UCLASS()
class THERITE_API AGameFlowPacifierLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameFlowPacifierLevel();

//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
//---------------- Initiliatization Methods
	void BindColliderMethods();
	void InitializeValues();
	
	UFUNCTION()
	void OnLightsOnEvent(AInteractor* Interactor);
	
	void PlaceBlockingVolume(FVector NewLocation, FRotator NewRotation);
	void ResetBlockingVolumePosition();
	
	void RaiseAmbientVolume(float newVolumeMultiplier);
	void ResetAmbientVolume();
	
	UFUNCTION()
	void EndGame();
	
//---------------- Bind Colliders Methods
	UFUNCTION()
	void OnTriggerLightsOutEventOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnTriggerStairsTiffanyEventOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	
	UFUNCTION()
	void OnTriggerDestroyTiffanyBedRoomOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerLucyRoomOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerLucyRoomOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerEndGamePassOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
public:
	
private:
	bool bLightsOutEventDone;
	bool bLightsDown;

	bool bEndGamePassDone = false;
	
	UPROPERTY(EditAnywhere, Category= "Settiings")
	float EmergencyLightsIntensity = 25.f;

	FVector BlockingVolumeOriginalLocation;
	
//-------- Colliders
	UPROPERTY(EditAnywhere, Category = "Colliders")
	ABlockingVolume* BlockingVolume;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_LightsOut;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_LucyRoom;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_TiffanyStairsEvent;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_TiffanyBedRoom;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_EndGmaePass;

//-------- Meshes
	UPROPERTY(EditAnywhere, Category= "Skeletals")
	ASkeletalMeshActor* Skeletal_TiffanyBedRoom;
	
	UPROPERTY(EditAnywhere, Category= "Skeletals")
	ASkeletalMeshActor* Skeletal_TiffanyStairs;
	
//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Audios")
	AAmbientSound*  AudioComponent_Ambient;
	UPROPERTY(EditAnywhere, Category = "Audios")
	AAmbientSound* AudioComponent_StressSound;
	UPROPERTY(EditAnywhere, Category = "Audios")
	AAmbientSound*  AudioComponent_Voices;

	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_Ambient;

	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_StressSound;

	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_Voices;
	
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_LightsOut;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_PowerDowns;

	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_PowerRestored;

	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_TiffanyNear;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_EndGame;

//-------- Lights
	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ALightsTheRite*> Lights_AllLights;

	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ACandle*> Candles_EndGame;

//-------- Flows & Puzzles
	FTimerHandle Timer_BedRoomEvent;
	
	FTimerHandle Timer_FirstStairsEvent;
	FTimerHandle Timer_SecondEvent;
	FTimerHandle Timer_ThirdEvent;
	
//-------- Target points
	UPROPERTY(EditAnywhere, Category="Target Point")
	ATargetPoint* TargetPoint_TiffanyStairClosePosition;
	
	UPROPERTY(EditAnywhere, Category="Target Point")
	ATargetPoint* TargetPoint_CorridorBlockingVolumeLocation;
	
//-------- Doors
	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_BedRoom;

	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_EndGame;
	
	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_BathRoomRoom;
	
//-------- Flows & Puzzles
	UPROPERTY(EditAnywhere, Category="Flows")
	AFetusPuzzle* GameFlow_FetusPuzzle;
	
	UPROPERTY(EditAnywhere, Category="Light Switch")
	ALightSwitch* LightSwitch_TermicalSwitch;

	UPROPERTY(EditAnywhere, Category="Objects")
	ALadder* AtticLader;
	
	UPROPERTY(EditAnywhere, Category="Light")
	TArray<AEmergencyLights*> EmergencyLights;

	UPROPERTY(EditAnywhere, Category="Setter")
	ABasePlayerSettingsSetter* PlayerSettingsSetter;
	
	AAlex* Player;
};