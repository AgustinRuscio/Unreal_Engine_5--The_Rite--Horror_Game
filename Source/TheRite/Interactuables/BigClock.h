//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "BigClock.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClockPuzzleFinished);

class AAlex;
class ATargetPoint;

UCLASS()
class THERITE_API ABigClock : public AInteractor
{
	GENERATED_BODY()
	
public:	
	ABigClock();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction() override;

	void SetReadyToUse();
	
private:
	UFUNCTION()
	void LeaveFocus();

//--------------------- Objects methods
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
public:
	FOnClockPuzzleFinished OnClockPuzzleCompleted;
	
private:
	bool bIsFocus;
	bool bReadyToUse;
	bool TimeLineMooving = false;

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
	
	//-------- Mesh / Colliders
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BigClockMesh;

	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* ClockPendulum;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* HourNeedleMesh;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* MinuturesNeedleMesh;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* CenterMesh;

	TArray<UStaticMeshComponent*> AllNeedles;
	UStaticMeshComponent* CurrentSelected;

	//-------- Audios
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFX_NeeddleMoving;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFX_ClockLocked;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFX_PuzzleComplete;
	
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
	
	FTimeline MoveNeedleTimeLine;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UCurveFloat* CurveFloat;
	
	AAlex* Player;
};