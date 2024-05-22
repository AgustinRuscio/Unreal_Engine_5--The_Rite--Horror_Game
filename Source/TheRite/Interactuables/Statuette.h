//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "Statuette.generated.h"

class UMaterialInterface;
class UMaterialInstanceDynamic;
class AStaticMeshActor;

UCLASS()
class THERITE_API AStatuette : public AInteractor
{
	GENERATED_BODY()

public:
	AStatuette();
	
//---------------- Getter Methods
	bool IsFirstInteraction() const;
	float GetDesiredRotation() const;
	float GetRotatioToAdd() const;
	FRotator GetRotation() const;
	
//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Interaction() override;
	
//---------------- Action Methods
	void EnableInteraction();
	void RestoreInitialValues();
	void SetAltarPosition(FVector pos, FRotator rot);
	void SetBase(AStaticMeshActor* base);

private:
//---------------- TimeLine Methods
	void BindTimeLine();
	
	UFUNCTION()
	void OpenTimeLineUpdate(float value);
	
private:
	UPROPERTY(EditAnywhere, Category="Settings")
	float DesireRotation;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	float RotationToAdd;
	
	bool bFirstInteraction = true;
	
	float InitialLightIntensity;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveDir;
	
	FVector InitialObjectPosition;
	FVector EndLocation;

	FVector InitialBasePosition;
	FVector EndBaseLocation;
	
	UPROPERTY(EditAnywhere, meta=(bAllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	AStaticMeshActor* BaseMesh;

	UPROPERTY(EditAnywhere, Category= "Settings")
	USoundBase* InteractionSound;

	UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynamicMaterial;
	
	FTimeline InteractionTimeLine;

	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* TimeLineCurve;
};