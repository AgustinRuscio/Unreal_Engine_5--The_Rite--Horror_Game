#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "LevelSequence.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/DoorKey.h"
#include "TheRite/Interactuables/BaseDrawer.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "Engine/TargetPoint.h"
#include "TheRite/Interactuables/SpectralObstacle.h"
#include "TheRite/Interactuables/SpectralWrittings.h"
#include "ClockLevelDrawersPuzzle.generated.h"

UCLASS()
class THERITE_API AClockLevelDrawersPuzzle : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, Category = "Construction")
	ASpectralWrittings* KeySpectralWrittings;

	UPROPERTY(EditAnywhere, Category = "Construction")
	ASpectralObstacle* DestroyableSpectralIbstacle;

	
	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_WhereDidILeftTheKey;
	
	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_WhereIsTheDeamKey;

	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_AlexScream;
	
	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_ImLoosingMyMind;
	
	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_Steps;
	
	UPROPERTY(EditAnywhere, Category = "Audio: Drawers")
	USoundBase* SFX_HeavyBreath;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjetcs: Drawers")
	TMap<ABaseDrawer*, ATargetPoint*> Map_Drawers_Target;

	
	UPROPERTY(EditAnywhere, Category = "InGameObjetcs: Drawers")
	TSubclassOf<ADoorKey> KeySubclass;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects: Ambient")
	TArray<ALightsTheRite*> Lights;

	UPROPERTY(EditAnywhere, Category= "Sequence")
	ULevelSequence* SequenceFade;

	FTimeline DrawerTimeline;
	
	UPROPERTY(EditAnywhere, Category="Drawers", meta=(ToolTip = "4 sec, flat curve"))
	UCurveFloat* DrawerTimeLineCurve;

	UPROPERTY(EditAnywhere, Category = "InGameObjects: Doors")
	ADoor* ArtRoomDoor;

	AAlex* Player;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects: Drawers")
	int8 MinDrawerOpenedUntilscreams = 3;
	int8 DoOnceSpawnKey = 0;
	int8 DoOnceDrawers = 0;
	int8 DrawersOpened = 0;
	bool bOnDrawerPuzzle = true;
	bool bScreamFlipFlop = true;
	
	void SetDrawers();
	void BindTimeLine();
	void GetPlayer();

	void ResolveSpawnKey();
	
	UFUNCTION()
	void DrawerPuzzle(ABaseDrawer* Drawer);
	
	void SpawnArtRoomKey(ATargetPoint* SpawnPoint, ABaseDrawer* ParentDrawer);
	
	UFUNCTION()
	void OnDrawerKeyCollected();
	
	UFUNCTION()
	void OnDrawerTimelineFinished();
	
protected:
	virtual void BeginPlay() override;

public:	
	AClockLevelDrawersPuzzle();
	virtual void Tick(float DeltaTime) override;
};