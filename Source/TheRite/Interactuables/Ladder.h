//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Ladder.generated.h"

class UArrowComponent;
class ULevelSequence;
class UCameraComponent;

UCLASS()
class THERITE_API ALadder : public AInteractor
{
	GENERATED_BODY()
	
public:	
	ALadder();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction() override;
	
private:
	UFUNCTION()
	void OnCinematicFinished();
	
public:

private:
	bool bFlipFlop = true;
	
	FTransform NewLocation;
	
//-------- Meshes Collider
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* LadderMesh;
	
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

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* Camera;
};
