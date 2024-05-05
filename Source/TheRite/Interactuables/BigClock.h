//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/PointLightComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "BigClock.generated.h"

class AAlex;
class ATargetPoint;

UCLASS()
class THERITE_API ABigClock : public AInteractor
{
	GENERATED_BODY()
	
public:	
	ABigClock();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction() override;

	void SetReadyToUse();
	
private:
	UFUNCTION()
	void LeaveFocus();

//--------------------- Objects methods
	UFUNCTION()
	void PrevNeedle();
	
	UFUNCTION()
	void NextNeedle();

	UFUNCTION()
	void NeedleInteraction();

	
	void CheckNeedlesPosition();
//--------------------- TimeLine methods
	void BindTimeLine();

	UFUNCTION()
	void MoveNeedleTimeLineTick(float deltaTime);
	
	UFUNCTION()
	void MoveNeedleTimeLineFinished();
	
	
private:
	bool bIsFocus;
	bool bReadyToUse;
	
	int8 CurrentNeedle = 0;

	//-------- Mesh / Colliders
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BigClockMesh;
	
	//UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	//UStaticMeshComponent* HourNeedleMesh;
	//
	//UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	//UStaticMeshComponent* MinuturesNeedleMesh;

	//-------- Target Points
	UPROPERTY(EditAnywhere)
	ATargetPoint* NewCameraPosition;
	
	//-------- Time Line
	FTimeline MoveNeedleTimeLine;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UCurveFloat* CurveFloat;
	
	//-------- Lights
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UPointLightComponent* MinutesPointLight;
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UPointLightComponent* HoursPointLight;
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UPointLightComponent* CenterPointLight;

	
	AAlex* Player;
};