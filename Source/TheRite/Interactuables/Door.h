#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Widgets/LockedWidget.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "Door.generated.h"


class AAlex;

UCLASS()
class THERITE_API ADoor : public AInteractor
{
	GENERATED_BODY()
	
private:
	//-------- Mesh
	UPROPERTY(EditAnywhere, Category = "Door mesh")
	UStaticMeshComponent* DoorItself;
	
	UPROPERTY(EditAnywhere, Category = "Door mesh")
	UStaticMeshComponent* BaseFront;
	
	UPROPERTY(EditAnywhere, Category = "Door mesh")
	UStaticMeshComponent* BaseBack;

	UPROPERTY(EditAnywhere, Category = "Door mesh")
	USkeletalMeshComponent* LatchFront;
	
	UPROPERTY(EditAnywhere, Category = "Door mesh")
	USkeletalMeshComponent* LatchBack;

	UPROPERTY(EditAnywhere, Category = "Door mesh")
	UBoxComponent* BoxCollision;

	AAlex* Player;

	//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXDoorUnlocked;
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXDoorClinck;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXDoorLocked;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXVoiceLocked;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXDoorSlam;
	
	//--------- Widget

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULockedWidget> LockedUI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTutorialWidget> TutorialUI;
	
	UPROPERTY()
	ULockedWidget* LockedWidget;
	UPROPERTY()
	UTutorialWidget* TutorialWidget;

	FTimerHandle TutorialTimerHandle;

	bool bDoOnceTut;
	UPROPERTY(EditAnywhere, Category= "Settings")
	bool bIsTutorialDoor = false;
	
	//---- General
	bool bFlipFlop = true;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	bool bIsLocked;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	bool bNeedKey;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	bool bKeyUnlocked;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	bool bCanSoundItsLocked;
	
	bool bHolding;
	bool bIsLookingDoor;
	
	int8 FirstTimeKeySound = 0;
	int8 AudioCounterItsLocked = 0;

	UPROPERTY(EditAnywhere, Category= "Open angle")
	float FrontAngle;
	
	UPROPERTY(EditAnywhere, Category= "Open angle")
	float Sensitivity;
	
	float ItsLockedTimer;
	
	UPROPERTY(EditAnywhere, Category= "Its Locked CD")
	float ItsLockedCD = 60;

	float DoorTimer;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	float DoorCD;
	//---- Functions
	
	UFUNCTION()
	void ItsLocked();

	UFUNCTION()
	void LatchAnim();


	UFUNCTION()
	void LatchHolding(bool isOppening);
	
	UFUNCTION()
	void CheckDragDoor();

	UFUNCTION()
	void CheckIfLookingDoor();

	void BindTimeLines();

	//--------- Time Line
	FTimeline TimeLineOpenDoor;
	
	FTimeline TimeLineItsLocked;
	
	FTimeline TimeLineLatchAnim;
	FTimeline TimeLineLatchHold;
	
	FTimeline TimeLineHardClosing;

	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveOpenDoor;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* HardClosingCurve;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* LatchHoldCurve;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* ItsLockedCurve;

	
	UFUNCTION()
	void OpenCloseTimeLineUpdate(float value);
	
	UFUNCTION()
	void OpenCloseTimelineFinished();

	
	UFUNCTION()
	void ItLockedTimeLineUpdate(float value);
	
	UFUNCTION()
	void ItLockedTimelineFinished();

	
	UFUNCTION()
	void LatchAnimTimeLineUpdate(float value);
	
	UFUNCTION()
	void LatchAnimTimelineFinished();


	UFUNCTION()
	void LatchHoldTimeLineUpdate(float value);
	
	UFUNCTION()
	void LatchHoldTimelineFinished();

	
	UFUNCTION()
	void HardClosingTimeLineUpdate(float value);
	
	UFUNCTION()
	void HardClosingTimelineFinished();

	FRotator InitialRot;
	FRotator CurrentRot;
	
protected:
	virtual void BeginPlay() override;

public:	
	ADoor();
	virtual void Tick(float DeltaTime) override;

	void HideTutorial();
	virtual void Interaction() override;
	
	UFUNCTION()
	void Open();
	
	UFUNCTION()
	void Close();

	void AutomaticClose();
	
	UFUNCTION()
	void HardClosing();

	UFUNCTION()
	void ObteinKey();

	bool IsLocked() const;
	bool NeedKey() const;
	bool KeyUnlocked() const;
	void SetLockedState(bool lockednewState);
};