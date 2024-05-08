//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CloclLevelArtRoomEvent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FArtRoomClocklLevelStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FArtRoomClocklLevelEnd);


class ATriggerBox;
class ASpotLight;
class ASkeletalMeshActor;
class UPostProcessComponent;
class ATargetPoint;
class ALightsTheRite;
class ADoor;
class AAlex;
class ATiffany;

UCLASS()
class THERITE_API ACloclLevelArtRoomEvent : public AActor
{
	GENERATED_BODY()

public:
	ACloclLevelArtRoomEvent();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnEventStarted(AActor* OverlappedActor, AActor* OtherActor);
	
//---------------- TimeLine Methods
	void BindTimeLines();
	void TimeLinesTick(float DeltaTime);

	
	UFUNCTION()
	void DuringFirstTurnOffTick(float deltaTime);

	UFUNCTION()
	void FirstTurnOffFinished();

	
	UFUNCTION()
	void DuringFirstTurnOnTick(float deltaTime);

	UFUNCTION()
	void OnFirstTurnOnFinished();

	
	UFUNCTION()
	void DuringSecondTurnOnTick(float deltaTime);

	UFUNCTION()
	void OnSecondTurnOnFinished();

	

	UFUNCTION()
	void DuringThirdTurnOffTick(float deltaTime);

	UFUNCTION()
	void OnThirdTurnOffFinished();
	

	UFUNCTION()
	void DuringThirdTurnOnTick(float deltaTime);

	UFUNCTION()
	void OnThirdTurnOnFinished();
	

	UFUNCTION()
	void DuringLastTurnOffTick(float deltaTime);

	UFUNCTION()
	void OnLastTurnOffFinished();

	UFUNCTION()
	void DuringLastTurnOnTick(float deltaTime);

	UFUNCTION()
	void OnLastTurnOnFinished();
	
public:	
	FArtRoomClocklLevelStarted OnArtRoomEventStarted;
	FArtRoomClocklLevelEnd OnArtRoomEventFinished;
	
private:
	int8 DoOnce = 0;

	//-------- Colliders Meshes
	UPROPERTY(EditAnywhere, Category = "Triggers")
	ATriggerBox* StartTriggerBox;
	
	UPROPERTY(EditAnywhere, Category = "Tiffany")
	ASkeletalMeshActor* FloatingTiff1;
	
	UPROPERTY(EditAnywhere, Category = "Tiffany")
	ASkeletalMeshActor* FloatingTiff2;
	
	UPROPERTY(EditAnywhere, Category = "Tiffany")
	ASkeletalMeshActor* FloatingTiff3;
	
	UPROPERTY(EditAnywhere, Category = "Tiffany")
	ASkeletalMeshActor* FloatingTiff4;
	
	//-------- Audio
	UAudioComponent* HearthBeatComponent;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* LightSwitch;
	
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* SFXTiffanyTalksToAlex;
	
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* HeathBeatSFX;
	
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* TiffanyNearSFX;
	
	//-------- Target point
	UPROPERTY(EditAnywhere, Category = "Target points")
	ATargetPoint* RoomCenterTaregtPoint;

	UPROPERTY(EditAnywhere, Category = "Target points")
	ATargetPoint* CloserTargetPoint;

	UPROPERTY(EditAnywhere, Category = "InGameObjects")
	ATargetPoint* BlockingVolumeOriginalLocation;
	
	//-------- Target point
	FTimeline FirstTurnOffTimeLine;
	FTimeline FirstTurnOnTimeLine;
	
	FTimeline SecondTurnOffTimeLine;
	FTimeline SecondTurnOnTimeLine;
	
	FTimeline ThirdTurnOffTimeLine;
	FTimeline ThirdTurnOnTimeLine;
	
	FTimeline LastTurnOffTimeLine;
	FTimeline LastTurnOnTimeLine;

	
	UPROPERTY(EditAnywhere, Category="Curves")
	UCurveFloat* TurnOffCurve;
	
	UPROPERTY(EditAnywhere, Category="Curves")
	UCurveFloat* TurnOnCurve;
	
	//-------- Feed back
	UPROPERTY(EditAnywhere, Category="PostProcess")
	UPostProcessComponent* PostProcess;

	UPROPERTY(EditAnywhere, Category="PostProcess")
	UMaterial* PostProcessMaterialEvent;
	FPostProcessVolumeProperties originalPostProcessValues;
	
	//-------- Lights
	UPROPERTY(EditAnywhere, Category = "Lights")
	ALightsTheRite* ArtRoomLight;

	UPROPERTY(EditAnywhere, Category = "Lights")
	ASpotLight* SpotLight;
	
	UPROPERTY(EditAnywhere, Category = "Door")
	ADoor* ArtRoomDoor;

	UPROPERTY(EditAnywhere, Category = "Tiffany")
	ATiffany* StandTiffany;
	
	AAlex* Alex;
};