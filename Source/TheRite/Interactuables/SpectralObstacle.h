//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
	ASpectralObstacle();
	
	//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	
	//---------------- Destroy Methods
	UFUNCTION()
	void DestryoObject(UNiagaraComponent* comp);
	void ObstacleDestroy();

private:
	//---------------- TimeLines Methods
	void BindTimeLines();
	
	UFUNCTION()
	void FirstTimeLineUpdate(float time);
	
	UFUNCTION()
	void FirstTimelineFinished();
	
public:	
	FObstacleDestroyed OnObstacleDestroy;
	
private:
	UStaticMeshComponent* ParentStaticMesh;
	
	UPROPERTY(EditAnywhere, Category = "Construction")
	UBoxComponent* BoxCollider;
	
	UPROPERTY(EditAnywhere, Category = "Construction")
	USoundBase* SpectralSound;

	//-------- Feedback
	UPROPERTY(EditAnywhere, Category = "Construction")
	UNiagaraComponent* NiagaraSystemComponent;
	
	UPROPERTY(EditAnywhere, Category = "Construction")
	UMaterialInstance* Mat;
	
	UMaterialInstanceDynamic* DynamicMaterial;

	FTimerHandle WaitTimer;
	
	FTimeline FirstTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* BothTimeLineCurve;
	
	UPROPERTY(EditAnywhere, Category = "Construction")
	AActor* ParentActor;
};