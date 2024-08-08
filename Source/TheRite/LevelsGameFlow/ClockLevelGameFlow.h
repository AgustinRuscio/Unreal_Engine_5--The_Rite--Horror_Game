//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "ClockLevelGameFlow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPartOfClockGain);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBlockingHit);


class ACloclLevelArtRoomEvent;
class UAudioComponent;
class ATargetPoint;
class ATiffany;
class AAlex;
class ADoor;
class ALetter;
class AMinutesLetter;
class AHourLetter;
class ALightsTheRite;
class ABaseDrawer;
class ADoorKey;
class ATriggerVolume;
class ARecordPlayer;
class ABlockingVolume;
class ATriggerBox;
class AInteractor;
class AMoveTiffany;
class ABigClock;
class UTutorialWidget;
class ACandle;
class ASpotLight;
class AStaticMeshActor;

UCLASS()
class THERITE_API AClockLevelGameFlow : public AActor
{
	GENERATED_BODY()

public:
	AClockLevelGameFlow();
//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void HideTutorialWidget();
//---------------- Initialize Methods
	void SetAudioSettings();
	void BindPuzzleEvents();
	void BindEvents();
	void SetTutorialUI();
	
//---------------- Tick Methods
	void MakeTiffanyTalk(float time);
	void MakeBreath(float time);


//---------------- Letters Methods
	UFUNCTION()
	void GetMinutes();
	
	UFUNCTION()
	void GetHours();

	void CheckLetters();

	void MinutesCollected();

	UFUNCTION()
	void LockDoorsEndGame();
	
	UFUNCTION()
	void EndGame();
	
//---------------- Audio Methods
	UFUNCTION()
	void VoicesSoundSetOrigialVolumen();
	
	UFUNCTION()
	void VoicesSoundIncrease();
	
	UFUNCTION()
	void OnSoundPaused();
	
//---------------- Blocking volumen Methods
	void PlaceBlockingVolumen(FVector NewLocation, FRotator NewRot);

	void ResetBlockingVolumenPosition();
	
//---------------- Spawn Methods
	UFUNCTION()
	void SpawnPlanksOnDoor();

	UFUNCTION()
	void SpawnTiffanyForLibraryKeyCollected();

//---------------- Interaction Methods
	UFUNCTION()
	void OnLibraryKeyCollected();
	
	UFUNCTION()
	void OnWalkFinished();
	
	UFUNCTION()
	void OnInteractionWithLockedDoor(AInteractor* Interactor);
	
	UFUNCTION()
	void OnJumpscareFinished();
	
//---------------- TimeLine Methods
	void BindTimeLineMethods();
	
	UFUNCTION()
	void OnSecondJumpscareTimelineFinished();
	
//---------------- Bind Colliders Methods
	UFUNCTION()
	void OnOverlapFirstLibraryTriggerBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapBeginJumpscare(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnOverlapBeginJumpscareReady(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapBeginLockDoorsEndGame(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnOverlapBeginKnock(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnOverlapBeginCloseGarageDoor(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnTriggerEndGamePassOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
public:
	FOnPartOfClockGain OnPartOfClockGain;
	FBlockingHit OnBlockingHit;
	
private:
	bool bMinutes;
	bool bHours;
	bool bLibraryPuzzleStarted;
	bool bLibraryJumpScaredReady;
	bool IShouldGetOutOfHere;
	bool bEndGamePassDone = false;
	
	int8 DoOnceLibrary = 0;
	int8 DoOnceJumpscare = 0;
	int8 DoOnceJumpscareReady = 0;
	int8 HitCounterLibrary = 0;

	float TiffanyTalkTimer, TiffanyTalkCD = 15.0f;
	float BreathTimer, BreathCD = 15.0f;
	
	float AmbientMusicOriginalVolumen;
	float StressSoundOriginalVolumen;
	float VoicesSoundOriginalVolumen;


	//-------- Colliders
	UPROPERTY(EditAnywhere, Category = "Colliders")
	ABlockingVolume* BlockingVolume;

	UPROPERTY(EditAnywhere, Category = "Colliders")
	ATriggerBox* KnockTrigger;
	
	UPROPERTY(EditAnywhere, Category = "Colliders")
	ATriggerBox* CloseGaregeDoorTriggerVolumen;
	
	UPROPERTY(EditAnywhere, Category = "Colliders")
	ATriggerBox* Trigger_LockEndGameDoors;
	
	UPROPERTY(EditAnywhere, Category = "Colliders")
	AMoveTiffany* HallKeyEventMoveTiffanyTrigger;
	
	UPROPERTY(EditAnywhere, Category = "Colliders: Library")
	ATriggerBox* LibraryTriggerVolumenFirst;
	
	UPROPERTY(EditAnywhere, Category = "Colliders: Library")
	ATriggerVolume* LibraryTriggerVolumenJumpScared;

	UPROPERTY(EditAnywhere, Category = "Colliders: Library")
	ATriggerVolume* LibraryTriggerVolumenJumpScaredReady;
	
	UPROPERTY(EditAnywhere, Category= "Colliders")
	ATriggerVolume* TriggerVolume_EndGamePass;
	
	UPROPERTY(EditAnywhere, Category = "Walls")
	TArray<AStaticMeshActor*> Walls_EndGameWall;
	
	//-------- Audio
	UAudioComponent* AmbientMusicCompoenent;
	UAudioComponent* StressSoundMusicCompoenent;
	UAudioComponent* VoicesSoundMusicCompoenent;

	UPROPERTY(EditAnywhere, Category = "Ambient Sound")
	USoundBase* AmbientMusic;

	UPROPERTY(EditAnywhere, Category = "Ambient Sound")
	USoundBase* StressSound;
	
	UPROPERTY(EditAnywhere, Category = "Ambient Sound")
	USoundBase* VoicesSound;

	UPROPERTY(EditAnywhere, Category = "Ambient Audios")
	USoundBase* SFX_Knocking;
	
	UPROPERTY(EditAnywhere, Category = "Ambient Audios")
	USoundBase* SFX_LastAudio;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects: Audio")
	USoundBase* SFX_BigDoor;

	UPROPERTY(EditAnywhere, Category = "Audios: Tiffany")
	USoundBase* TiffanyTalkCue;
	
	UPROPERTY(EditAnywhere, Category = "Audios: Tiffany")
	USoundBase* DropSound;

	UPROPERTY(EditAnywhere, Category = "Audios: Tiffany")
	USoundBase* TiffanyBreathkCue;
	
	UPROPERTY(EditAnywhere, Category = "Audios: Library")
	USoundBase* SFX_TiffanyHeavyBreath;
	UPROPERTY(EditAnywhere, Category = "Audios: Library")
	USoundBase* SFX_Alex_IHateThatSong;
		
	UPROPERTY(EditAnywhere, Category = "Audios: Library")
	USoundBase* SFX_Alex_WhatwasThat;
	
	UPROPERTY(EditAnywhere, Category = "Audios: Library")
	USoundBase* SFX_TiffanyScream;
	
	UPROPERTY(EditAnywhere, Category = "Audios: Library")
	USoundBase* SFX_Heartbeat;

	UPROPERTY(EditAnywhere, Category = "Audios: Library")
	USoundBase* SFX_TiffanyNear;

	UPROPERTY(EditAnywhere, Category = "Audios: Library")
	USoundBase* SFX_TiffanyLaugh;

	UPROPERTY(EditAnywhere, Category = "Audios: Library")
	USoundBase* AudioIShouldGetOutOfHere;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_LightsBroken;

	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_LightSwitch;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* OhFuckAlexTalk;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* GetAwaylexTalk;
	
	
	//-------- Taregt Points
	UPROPERTY(EditAnywhere, Category = "Target Points")
	ATargetPoint* BlockingVolumeOriginalLocation;
	
	UPROPERTY(EditAnywhere, Category = "Target Points: Library")
	ATargetPoint* HallKeyEventTiffanySpawnPoint;
	
	UPROPERTY(EditAnywhere, Category = "Target Points: Library")
	ATargetPoint* BlockingVolumeLibraryEntrancePosition;
	
	UPROPERTY(EditAnywhere, Category = "Target Points: Library")
	ATargetPoint* BlockingVolumenLibraryPosition;

	//-------- Actor for event
	UPROPERTY(EditAnywhere, Category="Actors for event")
	TArray<AActor*> PlanksToBeSpawnOnTiffanyWalk;

	UPROPERTY(EditAnywhere, Category = "Actors for event")
	TArray<AActor*> ActorTobeDestroyOnEndgame;

	UPROPERTY(EditAnywhere, Category = "Actors for event")
	AStaticMeshActor* Actor_EndGamePassWall;

	UPROPERTY(EditAnywhere, Category = "Actors for event")
	TArray<ACandle*> Candles_EndGame;
	
	//-------- TimeLines
	FTimerHandle JumpscareHandleFirst;
	FTimerHandle JumpscareHandleSecond;
	
	FTimerHandle TutorialTimerHandle;
	
	FTimeline JumpscareSecondTimeLine;
	
	UPROPERTY(EditAnywhere, Category="Library", meta=(ToolTip = "0.4f sec, flat curve"))
	UCurveFloat* JumpscareFirstTimeLineCurve;
	
	UPROPERTY(EditAnywhere, Category="Library", meta=(ToolTip = "4 sec, flat curve"))
	UCurveFloat* JumpscareSecondTimeLineCurve;

	//-------- Ui
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTutorialWidget> TutorialUI;
	
	UPROPERTY()
	UTutorialWidget* TutorialWidget;
	
	//-------- Advance need puzzle
	UPROPERTY(EditAnywhere, Category = "Letters")
	AMinutesLetter* MinutesLetter;
	
	UPROPERTY(EditAnywhere, Category = "Letters")
	AHourLetter* HoursLetter;
	
	//-------- Lights
	UPROPERTY(EditAnywhere, Category = "Lights: Ambient")
	TArray<ALightsTheRite*> Lights;

	UPROPERTY(EditAnywhere, Category = "Lights: Library")
	TArray<ALightsTheRite*> LibraryLightsEvent;

	UPROPERTY(EditAnywhere, Category = "Lights: Library")
	ALightsTheRite* LibraryRoofLight;

	UPROPERTY(EditAnywhere, Category = "Lights: Central")
	ASpotLight* Light_Clock;
	
	//-------- Door
	UPROPERTY(EditAnywhere, Category = "Doors")
	ADoor* GarageDoor;

	UPROPERTY(EditAnywhere, Category = "Doors")
	ADoor* ArtRoomDoor;
	
	UPROPERTY(EditAnywhere, Category = "Doors")
	ADoor* BigLockedDoor;

	UPROPERTY(EditAnywhere, Category = "Doors")
	ADoor* LibraryDoor;

	UPROPERTY(EditAnywhere, Category = "Doors: Key")
	ADoorKey* LibraryKey;

	
	UPROPERTY(EditAnywhere, Category= "Level Events")
	ACloclLevelArtRoomEvent* ArtRoomEvent;
	
	UPROPERTY(EditAnywhere, Category = "InGameObject: Library")
	ARecordPlayer* RecordPlayer;

	UPROPERTY(EditAnywhere, Category = "Tiffany")
	TSubclassOf<ATiffany> TiffanyClassForSpawning;
	ATiffany* MidleTiff;
	
	UPROPERTY(EditAnywhere, Category = "Tiffany")
	ATiffany* LibraryTiffany;
	
	UPROPERTY(EditAnywhere, Category = "Clock")
	ABigClock* BigClock;
	
	AAlex* Player;
};