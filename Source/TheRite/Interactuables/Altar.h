//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Altar.generated.h"

class AAltarWhell;
class UChangingdWidget;
class AAlex;
class ATargetPoint;

UCLASS()
class THERITE_API AAltar : public AInteractor
{
	GENERATED_BODY()

public:
	AAltar();

	virtual void Interaction() override;

	void DisableAltarInteraction();
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void DisableInteraction();
	
	UFUNCTION()
	void LeaveFocus();
	
//--------------------- Actions methods
	UFUNCTION()
	void WheelInteraction();

	UFUNCTION()
	void PrevWheel();

	UFUNCTION()
	void NextWheel();

	void ChangeCameraPosition();
	
//--------------------- TimeLine methods
	void BindTimeLine();
	
	UFUNCTION()
	void MoveCameraTick(float deltaSecinds);
	
	UFUNCTION()
	void MoveCameraFinished();

private:
	bool bIsFocus;

	int WhellIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Setting")
	FVector ExittingVector;
	
	UPROPERTY(EditAnywhere, Category = "Setting")
	FRotator ExittingRotation;
	
	FVector cameraPos;
	
	FVector3d ActualCamaraPos;
	FVector3d NextCamaraPos;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	TArray<AAltarWhell*> Whells;

	FTimeline MoveCameraTimeLine;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TArray<ATargetPoint*> CameraPos;
	
	AAlex* Player;
};