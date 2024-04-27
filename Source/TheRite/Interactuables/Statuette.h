//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "Statuette.generated.h"

class UPointLightComponent;

UCLASS()
class THERITE_API AStatuette : public AInteractor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta=(bAllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	UPointLightComponent* PointLight;

	float InitialLightIntensity;
	FVector InitialObjectPosition;
	FVector EndLocation;

	UPROPERTY(EditAnywhere, Category= "Settings")
	USoundBase* InteractionSound;

	FTimeline InteractionTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* TimeLineCurve;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveDir;

	bool bFirstInteraction = true;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OpenTimeLineUpdate(float value);

public:	
	AStatuette();
	virtual void Tick(float DeltaSeconds) override;

	virtual void Interaction() override;

	void RestoreInitialValues();
	void SetAltarPosition(FVector pos, FRotator rot);

	bool IsFirstInteraction() const;
	void EnableInteraction();
};