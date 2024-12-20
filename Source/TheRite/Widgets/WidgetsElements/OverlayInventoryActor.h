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
	
private:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Activate();
	UFUNCTION()
	void DeActivate();
	
private:
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* ItemMesh;
	
	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* SceneCaptureComponent2D;
	
	UPROPERTY(EditAnywhere)
	UPointLightComponent* PointLightComponent;

	class AAlex* PlayerRef;
};