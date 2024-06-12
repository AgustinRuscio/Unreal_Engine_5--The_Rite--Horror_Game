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
	
public:
	AAltarWhell();
	bool CheckRotation();
	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	virtual void Interaction() override;
	
	void EnableInteraction();
	void DisableInteraction();
	void StatuetteReady();

	void ASignValues(AStatuette* Statuette, float DesiredRotation, float RotationToAdd);
	
private:
	void BindTimeLines();
	UFUNCTION()
	void MoveTimeLineTick(float deltaSeconds);
	
	UFUNCTION()
	void MoveTimeLineFinisehd();
	
private:
	float DesiredRotation;
	float RotationToAdd;

	bool bStatuette;
	
	FRotator InteractionRotator;
	FRotator StatuateRotator;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category= "SFX")
	USoundBase* SFX_Rotation;
	
	FTimeline MoveTimeLine;

	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UCurveFloat* CurveFloat;
	
	AStatuette* Statuette;
};