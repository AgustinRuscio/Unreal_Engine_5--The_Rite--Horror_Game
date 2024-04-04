//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/Actor.h"
#include "OverlayInventoryActor.generated.h"

UCLASS()
class THERITE_API AOverlayInventoryActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* ItemMesh;
	
	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* SceneCaptureComponent2D;

	UPROPERTY(EditAnywhere)
	UPointLightComponent* PointLightComponent;
protected:
	virtual void BeginPlay() override;

public:	
	AOverlayInventoryActor();
};