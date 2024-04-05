//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "LevelSequence.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "RedDoor.generated.h"

UCLASS()
class THERITE_API ARedDoor : public AInteractor
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
	
	UPROPERTY(EditAnywhere, Category = "Door mesh")
	UStaticMeshComponent* EmmisivePlane;

	//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXDoor;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFXRedDoor;

	
	FTimeline TimeLineOpenDoor;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveOpenDoor;

	
	FTimeline TimeLineLatchAnim;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* ItsLockedCurve;

	FTimeline FadeTimeLine;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FadeCurve;

	UPROPERTY(EditAnywhere, Category = "Fade")
	ULevelSequence* SequenceFade;
	
	bool bAlreadyOpen;

	UPROPERTY(EditAnywhere, Category = "States")
	FName NextLevelName;

	
private:
	void BindTimeLines();
	void CreateEditorComponents();
	
	UFUNCTION()
	void OpenTimeLineUpdate(float value);
	
	UFUNCTION()
	void OpenTimelineFinished();

	
	UFUNCTION()
	void FadeTimelineFinished();

	
	UFUNCTION()
	void LatchAnimTimeLineUpdate(float value);


	UFUNCTION()
	void ChangeLevel();

protected:
	virtual void BeginPlay() override;
	virtual void Interaction() override;
	
public:	
	ARedDoor();
	virtual void Tick(float DeltaTime) override;
};