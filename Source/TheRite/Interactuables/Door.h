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
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ADoor();
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	//-------- Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door mesh")
	UStaticMeshComponent* DoorItself;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door mesh")
	UStaticMeshComponent* BaseFront;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door mesh")
	UStaticMeshComponent* BaseBack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door mesh")
	UStaticMeshComponent* KeyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door mesh")
	UStaticMeshComponent* NumberMesh0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door mesh")
	UStaticMeshComponent* NumberMesh1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door mesh")
	USkeletalMeshComponent* LatchFront;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door mesh")
	USkeletalMeshComponent* LatchBack;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door mesh")
	UBoxComponent* BoxCollision;
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
//---------------- Getter Methods
	bool IsLocked() const;
	bool NeedKey() const;
	bool KeyUnlocked() const;
	
//---------------- System Class Methods
	virtual void Interaction() override;

//---------------- Action Door Methods
	UFUNCTION()
	void ObtainKey();
	void UnlockDooUnlockedFromSisterDoor();
	
	UFUNCTION()
	void Open();
	
	UFUNCTION()
	void Close();

	UFUNCTION()
	void HardClosing();
	
	void AutomaticClose();
	
//---------------- Setter Methods
	void SetDoorKeyValues(FString itemName, PickableItemsID id);
	void SetCanDragState(bool newDragState);
	void SetLockedState(bool LockedNewState);

protected:
	//*****************************************************************************//
	//								PROTECTED VARIABLES							   //
	//*****************************************************************************//
	//-------- Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* SFXDoorUnlocked;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXDoorClinck;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXDoorLocked;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXVoiceLocked;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXDoorSlam;
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
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
	UPROPERTY(EditAnywhere, Category= "Settings")
	bool bDisapearKey = false;
	
	bool bHolding;
	bool bIsLookingDoor;
	bool bWasLookingDoor;
	bool bcanDrag;
	bool bIsPlayerForward;
	bool bDoOnceTut;
	bool bOpenFromSisterDoor;
	bool bTimeLineOpen;

	bool bDoOnceOpenLatchAnim = true;
	bool bLatchPlay = true;
	bool bLatchReversePlay = true;
	
	int8 FirstTimeKeySound = 0;
	int8 AudioCounterItsLocked = 0;

	UPROPERTY(EditAnywhere, Category= "Open angle")
	float FrontAngle;
	
	UPROPERTY(EditAnywhere, Category= "Open angle")
	float Sensitivity;
	
	float ItsLockedTimer;
	
	UPROPERTY(EditAnywhere, Category= "Its Locked CD")
	float ItsLockedCD = 60;

	float CurrentYaw;
	float LastYaw = 1604;
	
	float DoorTimer;
	
	float FirstYawrotation;
	float MaxYawrotation;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	float DoorOpenOffsetCD;

	FVector forward;

	FVector KeyStartLocation;
	FVector KeyEndLocation;
	
	FRotator InitialRot;
	FRotator CurrentRot;

	UPROPERTY(EditAnywhere, Category= "Settings")
	FRotator CloseRotation;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	FRotator OpenRotation;
	
	FRotator CurrentRotation;
	
	FString keyName;
	PickableItemsID keyId;
	
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
	FTimerHandle UnlockedDoorTimerHandle;
	
	FTimeline TimeLineOpenDoor;
	
	FTimeline TimeLineItsLocked;
	
	FTimeline TimeLineLatchAnim;
	FTimeline TimeLineLatchHold;
	
	FTimeline TimeLineHardClosing;
	FTimeline TimeLineUnlockDoor;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveUnlockDoor;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveOpenDoor;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* HardClosingCurve;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* LatchHoldCurve;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* ItsLockedCurve;

	UPROPERTY(EditAnywhere, Category = "Settings")
	ADoor* SisterDoor;
	
	AAlex* Player;
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
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

	void CalculateRotation();
	
	UFUNCTION()
	void CheckDragDoor();

	UFUNCTION()
	void CheckIfLookingDoor();

//---------------- FeedBack Methods

	void UnlockDoorWithKey();
	UFUNCTION()
	void ItsLocked();

	UFUNCTION()
	void LatchAnim();
	
	UFUNCTION()
	void LatchHolding(bool isOppening);

//---------------- TimeLines Methods
	void HideTutorialWidget();
	
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
	void HardClosingTimelineFinished();

	UFUNCTION()
	void UnlockDoorTimeLineTick(float value);
	
	UFUNCTION()
	void UnlockDoorTimeLineFinished();
};