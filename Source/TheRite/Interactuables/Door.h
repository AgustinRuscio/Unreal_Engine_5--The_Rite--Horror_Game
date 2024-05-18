//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"


class AAlex;
class UBoxComponent;
class ULockedWidget;
class UTutorialWidget;

UCLASS()
class THERITE_API ADoor : public AInteractor
{
	GENERATED_BODY()

public:
	ADoor();

//---------------- Getter Methods
	bool IsLocked() const;
	bool NeedKey() const;
	bool KeyUnlocked() const;
	
//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction() override;

//---------------- Action Door Methods
	UFUNCTION()
	void ObteinKey();
	
	UFUNCTION()
	void Open();
	
	UFUNCTION()
	void Close();

	UFUNCTION()
	void HardClosing();
	
	void AutomaticClose();
	
//---------------- Setter Methods
	void SetDoorKeyValues(FString itemName, PickableItemsID id);
	void SetCanDragFalse();
	void SetLockedState(bool lockednewState);

private:
//---------------- Initializer Methods
	void CreateWidgets();
	void InitializeNeededValues();
//---------------- Tutorial Methods
	void SetTutorialDoor();
	void TutorialInteraction();

//---------------- Checker Methods
	void HoldingTimerRunner(float DeltaTime);
	void CheckCanSound(float DeltaTime);

	void CheckPlayerForward();
	void CheckLocked();

	
	UFUNCTION()
	void CheckDragDoor();

	UFUNCTION()
	void CheckIfLookingDoor();

//---------------- FeedBack Methods
	UFUNCTION()
	void ItsLocked();

	UFUNCTION()
	void LatchAnim();
	
	UFUNCTION()
	void LatchHolding(bool isOppening);

//---------------- TimeLines Methods
	void BindTimeLines();
	void RunTimeLinesTick(float DeltaTime);

	
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
	void HardClosingTielineFinished();

private:
	
	UPROPERTY(EditAnywhere, Category= "States")
	bool DEBUGGING;
	UPROPERTY(EditAnywhere, Category= "States")
	bool bFrontOpen;
	
	bool bFlipFlop = true;
	
	UPROPERTY(EditAnywhere, Category = "States")
	bool bIsLocked;
	
	UPROPERTY(EditAnywhere, Category = "States")
	bool bNeedKey;
	
	UPROPERTY(EditAnywhere, Category = "States")
	bool bKeyUnlocked;
	
	UPROPERTY(EditAnywhere, Category = "States")
	bool bCanSoundItsLocked;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	bool bIsTutorialDoor = false;
	
	bool bHolding;
	bool bIsLookingDoor;
	bool bWasLookingDoor;
	bool bcanDrag;
	bool bIsPlayerForward;
	bool bDoOnceTut;
	
	int8 FirstTimeKeySound = 0;
	int8 AudioCounterItsLocked = 0;

	UPROPERTY(EditAnywhere, Category= "Open angle")
	float FrontAngle;
	
	UPROPERTY(EditAnywhere, Category= "Open angle")
	float Sensitivity;
	
	float ItsLockedTimer;
	
	UPROPERTY(EditAnywhere, Category= "Its Locked CD")
	float ItsLockedCD = 60;

	float curretnYaw;
	
	float DoorTimer;
	
	float FirstYawrotation;
	float MaxYawrotation;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	float DoorOpenOffsetCD;
	
	
	FRotator InitialRot;
	FRotator CurrentRot;

	UPROPERTY(EditAnywhere, Category= "Settings")
	FRotator CloseRotation;
	FRotator CurrentRotation;
	
	FString keyName;
	PickableItemsID keyId;
	
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

	//--------- Time Line
	FTimerHandle TutorialTimerHandle;
	
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
	
	AAlex* Player;
};