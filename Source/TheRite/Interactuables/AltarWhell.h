//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "AltarWhell.generated.h"

class AStatuette;

UCLASS()
class THERITE_API AAltarWhell : public AInteractor
{
	GENERATED_BODY()
	
private:
	float DesiredRotation;
	float RotationToAdd;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	FTimeline MoveTimeLine;

	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UCurveFloat* CurveFloat;

	FRotator InteractionRotator;
	FRotator StatuateRotator;

	AStatuette* Statuette;
	
	UFUNCTION()
	void MoveTimeLineTick(float deltaSeconds);
	
	UFUNCTION()
	void MoveTimeLineFinisehd();

protected:
	virtual void BeginPlay() override;

public:	
	AAltarWhell();
	virtual void Tick(float DeltaTime) override;

	virtual void Interaction() override;

	bool CheckRotation();
	void EnableInteraction();
	void DisableInteraction();

	void ASignValues(AStatuette* Statuette, float DesiredRotation, float RotationToAdd);
};