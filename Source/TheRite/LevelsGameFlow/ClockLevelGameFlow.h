//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "CloclLevelArtRoomEvent.h"
#include "Engine/BlockingVolume.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/TargetPoint.h"
#include "Engine/TriggerBox.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Door.h"

#include "TheRite/Characters/Alex.h"
#include "TheRite/Characters/Tiffany.h"
#include "TheRite/Interactuables/BaseDrawer.h"
#include "TheRite/Interactuables/DoorKey.h"
#include "TheRite/Interactuables/HourLetter.h"
#include "TheRite/Interactuables/LockedDoor.h"
#include "TheRite/Interactuables/MinutesLetter.h"
#include "TheRite/Interactuables/RecordPlayer.h"
#include "TheRite/Triggers/MakeTiffanyWalk.h"
#include "ClockLevelGameFlow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPartOfClockGain);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBlockingHit);

UCLASS()
class THERITE_API AClockLevelGameFlow : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, Category= "Level Events")
	ACloclLevelArtRoomEvent* ArtRoomEvent;
	
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* AmbientMusic;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* StressSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* VoicesSound;


	UAudioComponent* AmbientMusicCompoenent;
	UAudioComponent* StressSoundMusicCompoenent;
	UAudioComponent* VoicesSoundMusicCompoenent;
		
	float AmbientMusicOriginalVolumen;
	float StressSoundOriginalVolumen;
	float VoicesSoundOriginalVolumen;
	
	//UPROPERTY(EditAnywhere, Category = "Widgets")
	//TSubclassOf<UHintsWidget> HintsUI;
	//UHintsWidget* HintsWidget;


	UPROPERTY(EditAnywhere, Category = "One item grab items")
	ATargetPoint* TiffanySpawnPointOneItem;

	
	UPROPERTY(EditAnywhere, Category = "Tiffany")
	TSubclassOf<ATiffany> MidTiff;
	ATiffany* MidleTiff;
	
	UPROPERTY(EditAnywhere, Category = "One item grab items: Triggers")
	AMakeTiffanyWalk* MakeTiffanyWalkBetweenDoors;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects: Doors")
	ADoor* GarageDoor;
	UPROPERTY(EditAnywhere, Category = "InGameObjects: Doors")
	ADoor* ArtRoomDoor;
	
	AAlex* Player; 
	//AHandLetter* PlayerHint;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects: Letter")
	ALetter* TiffanyFirstLetter;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects: Letter")
	AMinutesLetter* MinutesLetter;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects: Letter")
	AHourLetter* HoursLetter;

	UPROPERTY(EditAnywhere, Category = "InGameObjects: Ambient")
	TArray<ALightsTheRite*> Lights;

	UPROPERTY(EditAnywhere, Category = "InGameObjects: Drawers")
	TArray<ATargetPoint*> DrawersTargetsPoint;

	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_WhereDidILeftTheKey;
	
	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_WhereIsTheDeamKey;
	
	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_ImLoosingMyMind;
	
	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_AlexScream;

	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_Steps;

	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_HeavyBreath;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjetcs: Drawers")
	TMap<ABaseDrawer*, ATargetPoint*> Map_Drawers_Target;

	UPROPERTY(EditAnywhere, Category = "InGameObjetcs: Drawers")
	TSubclassOf<ADoorKey> KeySubclass;
	
	//UPROPERTY(EditAnywhere, Category = "InGameObjects: Drawers")
	//ADoor* DrawerPuzzleDoor;

	FTimeline DrawerTimeline;

	UPROPERTY(EditAnywhere, Category = "InGameObjects: Library")
	ADoorKey* LibraryKey;

	UPROPERTY(EditAnywhere, Category = "InGameObjects: Library")
	ATargetPoint* TiffanySpawnPoint;

	UPROPERTY(EditAnywhere, Category = "InGameObjects: Library")
	AMakeTiffanyWalk* MakeTiffanyWalk;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects: Library")
	ATargetPoint* BlockingVolumeEntrancePosition;

	UPROPERTY(EditAnywhere, Category = "InGameObjects")
	ALockedDoor* BigLockedDoor;

	UPROPERTY(EditAnywhere, Category = "InGameObjects: Audio")
	USoundBase* SFX_BigDoor;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects")
	ABlockingVolume* BlockingVolume;
	UPROPERTY(EditAnywhere, Category = "InGameObjects")
	ATargetPoint* BlockingVolumeOriginalLocation;

	UPROPERTY(EditAnywhere, Category = "Audios: Tiffany")
	USoundBase* TiffanyTalkCue;
	
	UPROPERTY(EditAnywhere, Category = "Audios: Tiffany")
	USoundBase* DropSound;

	UPROPERTY(EditAnywhere, Category = "Audios: Tiffany")
	USoundBase* TiffanyBreathkCue;

	UPROPERTY(EditAnywhere, Category = "InGameObject: Library")
	ADoor* LibraryDoor;

	UPROPERTY(EditAnywhere, Category = "InGameObject: Library")
	ARecordPlayer* RecordPlayer;
	UPROPERTY(EditAnywhere, Category = "InGameObject: Library")
	ATargetPoint* BlockingVolumenLibraryPosition;

	
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
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_LightsBroken;
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_LightSwitch;

	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_Knocking;

	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* OhFuckAlexTalk;
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* GetAwaylexTalk;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_LastAudio;
	
	UPROPERTY(EditAnywhere, Category = "InGameObject: Library")
	ATriggerBox* LibraryTriggerVolumenFirst;
	
	UPROPERTY(EditAnywhere, Category = "InGameObject: Library")
	ATriggerVolume* LibraryTriggerVolumenJumpScared;

	UPROPERTY(EditAnywhere, Category = "InGameObject")
	ATriggerBox* EndGameTriggerVolumen;
	
	UPROPERTY(EditAnywhere, Category = "InGameObject")
	ATriggerBox* KnockTrigger;
	 
	UPROPERTY(EditAnywhere, Category = "InGameObject")
	ATriggerBox* CloseGaregeDoorTriggerVolumen;
	
	
	UPROPERTY(EditAnywhere, Category = "InGameObject: Library")
	ALightsTheRite* LibraryRoofLight;
	
	UPROPERTY(EditAnywhere, Category = "InGameObject: Library")
	ATiffany* LibraryTiffany;

	UPROPERTY(EditAnywhere, Category = "InGameObject")
	TArray<AActor*> ActorTobeDestroyOnEndgame;
	
	UPROPERTY(EditAnywhere, Category = "InGameObject: Library")
	TArray<ALightsTheRite*> LibraryLightsEvent;
	
	FTimeline JumpscareFirstTimeLine;
	FTimeline JumpscareSecondTimeLine;

	UPROPERTY(EditAnywhere, Category="Library", meta=(ToolTip = "0.4f sec, flat curve"))
	UCurveFloat* JumpscareFirstTimeLineCurve;
	
	UPROPERTY(EditAnywhere, Category="Library", meta=(ToolTip = "4 sec, flat curve"))
	UCurveFloat* JumpscareSecondTimeLineCurve;

	UPROPERTY(EditAnywhere, Category="Drawers", meta=(ToolTip = "4 sec, flat curve"))
	UCurveFloat* DrawerTimeLineCurve;
	
	
	FTimerHandle PortraitTimerHandle;
	
	bool bMinutes;
	bool bHours;
	bool bOnDrawerPuzzle = true;
	bool bLibraryPuzzleStarted;
	bool bLibraryJumpScaredReady;
	bool bCanDrop;
	
	int8 DrawersOpened = 0;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects: Drawers")
	int8 MinDrawerOpenedUntilscreams = 3;
	
	int8 DoOnceDrawers = 0;
	int8 DoOnceLibrary = 0;
	int8 DoOnceJumpscare = 0;
	int8 DoOnceSpawnKey = 0;
	
	int8 HitCounterLibrary = 0;

	float TiffanyTalkTimer, TiffanyTalkCD = 15.0f;
	float BreathTimer, BreathCD = 15.0f;
	float PortraitTimer = 0.0f;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects: Portraits")
	float PortraitDownCD = 0.0f;
	
private:
	void SetVariables();
	void BindPuzzleEvents();

	UFUNCTION()
	void CheckInteraction();
	UFUNCTION()
	void AlexSayGetAway();

	UFUNCTION()
	void GetMinutes();
	UFUNCTION()
	void GetHours();
	
	UFUNCTION()
	void FirstLetterRead();
	//void HintUIOn();

	void MinutesCollected();

	UFUNCTION()
	void OnDrawerTimelineFinished();

	UFUNCTION()
	void VoicesSoundSetOrigialVolumen();
	UFUNCTION()
	void VoicesSoundIncrease();
	UFUNCTION()
	void SpawnPlanksOnDoor();

	UFUNCTION()
	void SpawnTiffanyForLibraryKeyCollected();

	UFUNCTION()
	void OnLibraryKeyCollected();
	UFUNCTION()
	void OnWalkFinished();
	
	UFUNCTION()
	void OnInteractionWithLockedDoor();

	
	void PlaceBlockingVolumen(FVector NewLocation, FRotator NewRot);

	void ResetBlockingVolumenPosition();

	void MakeTiffanyTalk(float time);
	void MakeBreath(float time);

	UFUNCTION()
	void OnSoundPaused();

	UFUNCTION()
	void OnOverlapFirstLibraryTriggerBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapBeginJumpscare(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapBeginEndGame(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnOverlapBeginKnock(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnOverlapBeginCloseGarageDoor(AActor* OverlappedActor, AActor* OtherActor);

	void BindTimLinemethods();
	
	UFUNCTION()
	void OnFirstJumpscareTimelineFinished();
	UFUNCTION()
	void OnSecondJumpscareTimelineFinished();
	UFUNCTION()
	void OnJumpscareFinished();

	UPROPERTY(EditAnywhere, Category="Event planks")
	TArray<AActor*> PlanksToBeSpawnOnTiffanyWalk;
protected:
	virtual void BeginPlay() override;

public:
	FOnPartOfClockGain OnPartOfClockGain;
	FBlockingHit OnBlockingHit;

public:	
	AClockLevelGameFlow();
	virtual void Tick(float DeltaTime) override;
};