//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "BigClock.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClockPuzzleFinished);

class AAlex;
class ATargetPoint;
class UTutorialWidget;
class UArrowComponent;

UCLASS()
class THERITE_API ABigClock : public AInteractor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ABigClock();

//-------- Mesh / Colliders
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BigClockMesh;

	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* ClockPendulum;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* HourNeedleMesh;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* MinuturesNeedleMesh;

	TArray<UStaticMeshComponent*> AllNeedles;
	UStaticMeshComponent* CurrentSelected;

	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UArrowComponent* FinallHourNeedleLocation;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnClockPuzzleFinished OnClockPuzzleCompleted;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	virtual void Interaction() override;

	void SetReadyToUse();
	
	void CompleteClock();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bIsFocus;
	bool bReadyToUse;

	bool bFirstInteraction = true;
	bool bFirstAfterCompleting = true;

	bool bIsClockComplete;

	UPROPERTY(EditAnywhere, Category = "Setting")
	bool bShowClue;
	
	bool TimeLineMoving = false;

	int8 CurrentNeedle = 0;
	
	UPROPERTY(EditAnywhere, Category = "Setting")
	float DesireHourRotation;

	UPROPERTY(EditAnywhere, Category = "Setting")
	float DesireMinutesRotation;
	
	UPROPERTY(EditAnywhere, Category = "Setting")
	FVector ExittingVector;
	
	UPROPERTY(EditAnywhere, Category = "Setting")
	FRotator ExittingRotation;
	
	UPROPERTY(EditAnywhere, Category = "Setting")
	FRotator RotationToAdd;

	FRotator InitialNeedleRotation;
	FRotator EndNeedleRotation = FRotator(16,04,03);

	FRotator LastMinutesRot = FRotator(16,04,03);
	FRotator LastHourRot = FRotator(16,04,03);

	//-------- Audios
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFX_NeeddleMoving;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFX_ClockLocked;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFX_PuzzleComplete;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFX_Clue;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFX_ClockNotReady;

	//-------- Widget
	UPROPERTY(EditAnywhere, Category= "Widgets")
	TSubclassOf<UTutorialWidget> WG_ClockClue;
	
	//-------- Target Points
	UPROPERTY(EditAnywhere, Category= "Settings")
	UMaterialInterface* SelectedNeedleMaterial;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	UMaterialInterface* NeedlebaseMaterial;
	
	//-------- Target Points
	UPROPERTY(EditAnywhere)
	ATargetPoint* NewCameraPosition;
	
	//-------- Time Line
	FTimerHandle WaitForAudioTimer;
	FTimerHandle Timer_ClockClue;
	
	FTimeline MoveNeedleTimeLine;
	FTimeline PutNeedleTimeLine;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UCurveFloat* CurveFloat;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	UCurveFloat* C2urveFloat;

	AAlex* Player;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
//--------------------- Action methods
	UFUNCTION()
	void LeaveFocus();
	
	UFUNCTION()
	void PrevNeedle();
	
	UFUNCTION()
	void NextNeedle();

	UFUNCTION()
	void NeedleInteraction();

	void ChangeNeedle();
	void CheckNeedlesPosition();
	
//--------------------- TimeLine methods
	void BindTimeLine();

	UFUNCTION()
	void MoveNeedleTimeLineTick(float deltaTime);
	
	UFUNCTION()
	void MoveNeedleTimeLineFinished();

	UFUNCTION()
	void PutNeedleNeedleTimeLineTick(float deltaTime);
	
	UFUNCTION()
	void PutneedleNeedleTimeLineFinished();
};