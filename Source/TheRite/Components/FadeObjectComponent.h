//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "FadeObjectComponent.generated.h"

class UMaterialInterface;
class UMaterialInstanceDynamic;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERITE_API UFadeObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFadeObjectComponent();
	
//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//---------------- Action Methods
	void SetMaterialAlpha(float alpha);
	void ActivateFade();
	void DeActivateFade();

	void PermanentActivation();
	
private:
	void ObtainOwnerMaterial();
	
//---------------- TimeLine Methods
	void BindTimeLine();
	
	UFUNCTION()
	void FadeTick(float deltaSeconds);
	UFUNCTION()
	void FadeFinished();

private:
	bool bFading = false;
	bool bPermanentTurnedOn = false;

	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> OwnerMesh;
	
	FTimeline FadeTimeLine;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	UCurveFloat* FadeCurve;
	
	UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynamicMaterial;
};