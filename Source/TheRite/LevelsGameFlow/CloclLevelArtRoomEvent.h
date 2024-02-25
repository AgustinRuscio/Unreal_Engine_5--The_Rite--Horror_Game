#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "Engine/SpotLight.h"
#include "Engine/TargetPoint.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Interactuables/Door.h"
#include "Engine/BlockingVolume.h"
#include "TheRite/Characters/Tiffany.h"
#include "CloclLevelArtRoomEvent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FArtRoomClocklLevelStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FArtRoomClocklLevelEnd);

UCLASS()
class THERITE_API ACloclLevelArtRoomEvent : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Triggers")
	ATriggerBox* StartTriggerBox;
	
	UPROPERTY(EditAnywhere, Category = "InGameObjects")
	ABlockingVolume* BlockingVolume;
	
	UPROPERTY(EditAnywhere, Category = "Lights")
	ALightsTheRite* ArtRoomLight;

	UPROPERTY(EditAnywhere, Category = "Lights")
	ASpotLight* SpotLight;

	UPROPERTY(EditAnywhere, Category = "Target points")
	ATargetPoint* BlockingVolumenPosition;
	UPROPERTY(EditAnywhere, Category = "Target points")
	ATargetPoint* RoomCenterTaregtPoint;
	UPROPERTY(EditAnywhere, Category = "Target points")
	ATargetPoint* CloserTargetPoint;
	UPROPERTY(EditAnywhere, Category = "InGameObjects")
	ATargetPoint* BlockingVolumeOriginalLocation;

	UPROPERTY(EditAnywhere, Category = "Door")
	ADoor* ArtRoomDoor;

	UPROPERTY(EditAnywhere, Category = "Tiffany")
	ATiffany* StandTiffany;
	
	UPROPERTY(EditAnywhere, Category = "Tiffany")
	ASkeletalMeshActor* FloatingTiff1;
	UPROPERTY(EditAnywhere, Category = "Tiffany")
	ASkeletalMeshActor* FloatingTiff2;
	UPROPERTY(EditAnywhere, Category = "Tiffany")
	ASkeletalMeshActor* FloatingTiff3;
	UPROPERTY(EditAnywhere, Category = "Tiffany")
	ASkeletalMeshActor* FloatingTiff4;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* LightSwitch;
	
	UPROPERTY(EditAnywhere, Category="Curves")
	UCurveFloat* TurnOffCurve;
	UPROPERTY(EditAnywhere, Category="Curves")
	UCurveFloat* TurnOnCurve;
	
	FTimeline FirstTurnOffTimeLine;
	FTimeline FirstTurnOnTimeLine;
	FTimeline SecondTurnOffTimeLine;
	FTimeline SecondTurnOnTimeLine;
	FTimeline ThirdTurnOffTimeLine;
	FTimeline ThirdTurnOnTimeLine;
	FTimeline LastTurnOffTimeLine;
	FTimeline LastTurnOnTimeLine;

	int DoOnce = 0;
	
	void BindTimeLines();

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

protected:
	virtual void BeginPlay() override;

public:	
	ACloclLevelArtRoomEvent();
	
	virtual void Tick(float DeltaTime) override;

	FArtRoomClocklLevelStarted OnArtRoomEventStarted;
	FArtRoomClocklLevelEnd OnArtRoomEventFinished;
	
	UFUNCTION()
	void OnEventStarted(AActor* OverlappedActor, AActor* OtherActor);
	void ResetBlockingVolumenPosition();
	void PlaceBlockingVolumen(FVector NewLocation, FRotator NewRotation);
};