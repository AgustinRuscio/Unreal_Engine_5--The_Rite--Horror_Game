//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AOverlayInventoryActor();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* ItemMesh;
	
	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* SceneCaptureComponent2D;
	
	UPROPERTY(EditAnywhere)
	UPointLightComponent* PointLightComponent;

	class AAlex* PlayerRef;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void Activate();
	UFUNCTION()
	void DeActivate();
};