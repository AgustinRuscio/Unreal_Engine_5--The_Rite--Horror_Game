//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "RedDoor.generated.h"

class ULevelSequence;
class UBoxComponent;

UCLASS()
class THERITE_API ARedDoor : public AInteractor
{
	GENERATED_BODY()

public:
	ARedDoor();
	
	virtual void Interaction() override;
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void CreateEditorComponents();
	
	UFUNCTION()
	void ChangeLevel();

//---------------- TimeLines Methods
	void BindTimeLines();

	
	UFUNCTION()
	void OpenTimeLineUpdate(float value);
	
	UFUNCTION()
	void OpenTimelineFinished();
	
	
	UFUNCTION()
	void LatchAnimTimeLineUpdate(float value);
	
	UFUNCTION()
	void FadeTimelineFinished();
	
private:
	bool bAlreadyOpen;

	UPROPERTY(EditAnywhere, Category = "States")
	FName NextLevelName;
	
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
	
	UPROPERTY(EditAnywhere, Category = "Door mesh")
	UStaticMeshComponent* EmmisivePlane;

//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXDoor;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXRedDoor;

	
	UPROPERTY(EditAnywhere, Category = "Fade")
	ULevelSequence* SequenceFade;

//-------- Time line
	FTimeline TimeLineOpenDoor;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveOpenDoor;

	
	FTimeline TimeLineLatchAnim;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* ItsLockedCurve;

	FTimeline FadeTimeLine;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FadeCurve;
};