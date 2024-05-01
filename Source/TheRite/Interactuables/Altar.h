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
	
private:
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	TArray<AAltarWhell*> Whells;

	bool bIsFocus;

	int WhellIndex = 0;

	AAlex* Player;

	void ChangeCameraPosition();

	FVector3d ActualCamaraPos;
	FVector3d NextCamaraPos;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TArray<ATargetPoint*> CameraPos;

	FVector cameraPos;
	
	FTimeline MoveCameraTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	UCurveFloat* CurveFloat;

	UFUNCTION()
	void MoveCameraTick(float deltaSecinds);
	UFUNCTION()
	void MoveCameraFinished();
	
	UFUNCTION()
	void LeaveFocus();
	UFUNCTION()
	void WhellInteraction();

	UFUNCTION()
	void PrevWhell();

	UFUNCTION()
	void NextWhell();

	void BindTimeLine();
	
protected:
	virtual void BeginPlay() override;

public:	
	AAltar();
	virtual void Tick(float DeltaTime) override;

	virtual void Interaction() override;


};