//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "SpectralObstacle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FObstacleDestroyed);


class UBoxComponent;
class UNiagaraComponent;
class UMaterialInstance;
class UMaterialInstanceDynamic;


UCLASS()
class THERITE_API ASpectralObstacle : public AInteractor
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ASpectralObstacle();
	
	UStaticMeshComponent* ParentStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Construction")
	UNiagaraComponent* NiagaraSystemComponent;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FObstacleDestroyed OnObstacleDestroy;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
//---------------- Destroy Methods
	UFUNCTION()
	void DestroyObject(UNiagaraComponent* comp);
	void ObstacleDestroy();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Construction")
	UBoxComponent* BoxCollider;
	
	UPROPERTY(EditAnywhere, Category = "Construction")
	USoundBase* SpectralSound;

	UPROPERTY(EditAnywhere, Category = "Construction")
	UMaterialInstance* Mat;
	
	UMaterialInstanceDynamic* DynamicMaterial;

	FTimeline FirstTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* BothTimeLineCurve;
	
	UPROPERTY(EditAnywhere, Category = "Construction")
	AActor* ParentActor;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

//---------------- TimeLines Methods
	void BindTimeLines();
	
	UFUNCTION()
	void FirstTimeLineUpdate(float time);
	
	UFUNCTION()
	void FirstTimelineFinished();
};