//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/TimelineComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "SpectralObstacle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FObstacleDestroyed);

UCLASS()
class THERITE_API ASpectralObstacle : public AInteractor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Construction")
	UBoxComponent* BoxCollider;
	UPROPERTY(EditAnywhere, Category = "Construction")
	UNiagaraComponent* NiagaraSystemComponent;

	UPROPERTY(EditAnywhere, Category = "Construction")
	USoundBase* SpectralSound;

	UStaticMeshComponent* ParentStaticMesh;
	UPROPERTY(EditAnywhere, Category = "Construction")
	AActor* ParentActor;

	UPROPERTY(EditAnywhere, Category = "Construction")
	UMaterialInstance* Mat;
	
	UMaterialInstanceDynamic* DynamicMaterial;

	FTimeline FirstTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* BothTimeLineCurve;
	
public:	
	ASpectralObstacle();
	virtual void BeginPlay() override;

	UFUNCTION()
	void FirstTimelineFinished();
	UFUNCTION()
	void FirstTimeLineUpdate(float time);

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	void DestryoObject(UNiagaraComponent* comp);
	void ObstacleDestroy();

	FObstacleDestroyed OnObstacleDestroy;
};