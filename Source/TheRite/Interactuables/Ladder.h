//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Ladder.generated.h"

class UArrowComponent;
class ULevelSequence;
class UCameraComponent;
class UBoxComponent;
class AAlex;

UCLASS()
class THERITE_API ALadder : public AInteractor
{
	GENERATED_BODY()
	
public:	
	ALadder();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction() override;

	void FirstInteraction();
	void NormalInteraction();
	
	void EnableLadder();
	void DisableLadder();
	
private:
	UFUNCTION()
	void OnCinematicFinished();

	UFUNCTION()
	void OnReLocationPlayerTimeLineTick(float delta);
	UFUNCTION()
	void OnReLocationPlayerTimeLineFinished();
	
public:

private:
	bool bFlipFlop = true;
	bool bFirstInteraction = true;
	bool bDoOnceOpenByNear = false;

	UPROPERTY(EditAnywhere, Category = "Distance")
	float DistanceToNearAnim = 20;
	
	FTransform PlayerTransform;

	FVector NewPlayerLocation;
	FRotator NewPlayerRotation;

	FVector POVLocation;
	FRotator POVRotation;
	
//-------- Meshes Collider
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* LadderMesh;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* LadderTop;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* LadderSkeletal;
	
	UPROPERTY(EditAnywhere, Category = "Collider", meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;

	//-------- Meshes Collider
	UPROPERTY(EditAnywhere, Category = "Animations", meta=(AllowPrivateAccess = "true"))
	UAnimationAsset* Animation_DisableLadder;
	
	UPROPERTY(EditAnywhere, Category = "Animations", meta=(AllowPrivateAccess = "true"))
	UAnimationAsset* Animation_EnableLadder;
	
	UPROPERTY(EditAnywhere, Category = "Animations", meta=(AllowPrivateAccess = "true"))
	UAnimationAsset* Animation_PartialOpen;
	
	UPROPERTY(EditAnywhere, Category = "Animations", meta=(AllowPrivateAccess = "true"))
	UAnimationAsset* Animation_FullyOpen;
//-------- Arrow
	UPROPERTY(EditAnywhere, Category = "Arrow", meta=(AllowPrivateAccess = true))
	UArrowComponent* InitialPosition;
	
	UPROPERTY(EditAnywhere, Category = "Arrow", meta=(AllowPrivateAccess = true))
	UArrowComponent* EndPosition;
	
//-------- Arrow
	UPROPERTY(EditAnywhere, Category= "Sequence")
	ULevelSequence* StairsUpCinematic;
	UPROPERTY(EditAnywhere, Category= "Sequence")
	ULevelSequence* StairsDownCinematic;

	FTimerHandle Timer_FullOpenAnim;
	FTimerHandle Timer_PartialOpenAnim;
	
	FTimeline Timer_ReLocatePlayerTimeLine;
	UPROPERTY(EditAnywhere, Category= "Sequence")
	UCurveFloat* CurveFloat;
	
	AAlex* player;
};
