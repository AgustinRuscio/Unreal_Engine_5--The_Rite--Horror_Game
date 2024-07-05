//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once
#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Fetus.h"
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
class AHideAndSeekPuzzle;
class ASkeletalMeshActor;
class ATargetPoint;
class AAmbientSound;
class AStaticMeshActor;
class AManikin;

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
	void PlaceMannequinsInCorridor(AInteractor* Interactor);
	
	UFUNCTION()
	void PlaceMannequinsStairs(AInteractor* Interactor);
	
	UFUNCTION()
	void LightsOnBedRoom(AInteractor* Interactor);

	UFUNCTION()
	void OnHideSeekPuzzleStarted();
	
	UFUNCTION()
	void EndGame();

	UFUNCTION()
	void OnLastPuzzleTimerTick(float deltaSeconds);

	UFUNCTION()
	void OnLasPuzzleTimerFinished();
	
	//---------------- Bind Colliders Methods
	UFUNCTION()
	void OnTriggerLightsOutEventOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnTriggerStairsTiffanyEventOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerEndGamePassOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
private:
	bool bLightsOutEventDone = false;
	bool bLightsDown = false;
	bool bLightsRestored = false;
	
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
	ATriggerVolume* TriggerVolume_TiffanyStairsEvent;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_EndGmaePass;

	//-------- Meshes
	UPROPERTY(EditAnywhere, Category= "Meshes")
	ASkeletalMeshActor* Skeletal_TiffanyStairs;

	UPROPERTY(EditAnywhere, Category= "Meshes")
	TArray<AStaticMeshActor*> Meshes_HideSeekObjects;
	
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
	USoundBase* SFX_TiffanyBreath;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_EndGame;

	//-------- Lights
	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ALightsTheRite*> Lights_AllLights;

	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ACandle*> Candles_EndGame;

	//-------- Flows & Puzzles
	FTimerHandle Timer_FirstStairsEvent;
	FTimerHandle Timer_SecondEvent;
	FTimerHandle Timer_ThirdEvent;

	FTimeline Timer_LastPuzzleStarted;

	UPROPERTY(EditAnywhere, Category="Timer")
	UCurveFloat* CurveFloat_LastPuzzle;
	
	//-------- Target points
	UPROPERTY(EditAnywhere, Category="Target Point")
	ATargetPoint* TargetPoint_TiffanyStairClosePosition;
	
	UPROPERTY(EditAnywhere, Category="Target Point")
	ATargetPoint* TargetPoint_CorridorBlockingVolumeLocation;
	
	UPROPERTY(EditAnywhere, Category="Target Point")
	TArray<ATargetPoint*> TargetPoint_ScaryManiquiesPosition;

	UPROPERTY(EditAnywhere, Category="Target Point")
	TArray<ATargetPoint*> TargetPoint_NormalManiquiesNewPosition;

	UPROPERTY(EditAnywhere, Category="Target Point")
	TArray<ATargetPoint*> TargetPoint_CorridorManiquiesPosition;
	
//-------- Doors
	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_BedRoom;

	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_BathRoomRoom;
	
	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_EndGmae;
	
//-------- Flows & Puzzles
	//-------- Fetus
	UPROPERTY(EditAnywhere, Category="Flows")
	AFetusPuzzle* GameFlow_FetusPuzzle;
	
	UPROPERTY(EditAnywhere, Category="Flows")
	AHideAndSeekPuzzle* GameFlow_HideAndSeekPuzzle;

	UPROPERTY(EditAnywhere, Category="Flows")
	AFetus* MainFetus;
	
	//-------- Light Switch Event
	UPROPERTY(EditAnywhere, Category="Light Switch")
	ALightSwitch* LightSwitch_ThermalSwitch;

	UPROPERTY(EditAnywhere, Category="Actors")
	TArray<AStaticMeshActor*> Actors_ScaryMannequins;

	UPROPERTY(EditAnywhere, Category="Actors")
	TArray<AStaticMeshActor*> Actors_NormalMannequins;

	UPROPERTY(EditAnywhere, Category="Actors")
	TArray<AStaticMeshActor*> Actors_StairsMannequins;
	
	UPROPERTY(EditAnywhere, Category="Actors")
	TArray<AManikin*> A_CorridorMannequins;
	
	//-------- Fuse Event
	UPROPERTY(EditAnywhere, Category="Interactors")
	AInteractor* InteractorForManiquiesToAppear;
	
	UPROPERTY(EditAnywhere, Category="Objects")
	ALadder* AtticLadder;
	
	UPROPERTY(EditAnywhere, Category="Light")
	TArray<AEmergencyLights*> EmergencyLights;

	UPROPERTY(EditAnywhere, Category="Setter")
	ABasePlayerSettingsSetter* PlayerSettingsSetter;

	UPROPERTY(EditAnywhere, Category="Setter")
	AInteractor* Interactable_BedroomLightsOn;
	
	AAlex* Player;
};