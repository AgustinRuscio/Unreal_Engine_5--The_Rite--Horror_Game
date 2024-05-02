//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OverlayInventoryActor.generated.h"

class UPointLightComponent;
class USceneCaptureComponent2D;

UCLASS()
class THERITE_API AOverlayInventoryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AOverlayInventoryActor();
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* ItemMesh;
	
	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* SceneCaptureComponent2D;

	UPROPERTY(EditAnywhere)
	UPointLightComponent* PointLightComponent;
};