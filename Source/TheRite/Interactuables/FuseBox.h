//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "LightSwitch.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "FuseBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFuseBoxCompleted);

class UArrowComponent;

UCLASS()
class THERITE_API AFuseBox : public AInteractor
{
	GENERATED_BODY()
	
public:	
	AFuseBox();
	
//--------------------- System Class methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction() override;

	void GrabFusible();
	
private:
//--------------------- TimeLine methods
	UFUNCTION()
	void LocateFusibleTick(float deltaSeconds);
	
	UFUNCTION()
	void LocateFusibleFinished();
	
public:
	FFuseBoxCompleted OnFuseBoxComplete;
	
private:
	bool bHastFusibleToPut;
	bool bBothFusiblesSameTime;

	UPROPERTY(EditAnywhere, Category="Settings")
	int MaxFusiblesQuantity = 0;
	int FusiblesQuantity = 0;

//-------- Meshes Collider
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* FusibleBoxMesh;
	
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* FirstFusible;
	
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* SecondsFusible;
	
//-------- Arrow
	UPROPERTY(EditAnywhere, Category = "Arrow", meta=(AllowPrivateAccess = true))
	UArrowComponent* InitialPosition;
	
	UPROPERTY(EditAnywhere, Category = "Arrow", meta=(AllowPrivateAccess = true))
	UArrowComponent* EndFirstPosition;
	
	UPROPERTY(EditAnywhere, Category = "Arrow", meta=(AllowPrivateAccess = true))
	UArrowComponent* EndSecondPosition;
	
//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Feed back", meta=(AllowPrivateAccess = true))
	USoundBase* SFX_Sparking;

//-------- Time line
	FTimeline LocateFusibleTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Timeline", meta=(AllowPrivateAccess = true))
	UCurveFloat* LocateFusibleCurve;

	UPROPERTY(EditAnywhere, Category = "Timeline", meta=(AllowPrivateAccess = true))
	ALightSwitch* TermicalSwitch;
};