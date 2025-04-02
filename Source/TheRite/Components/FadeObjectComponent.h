//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	UFadeObjectComponent();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
//---------------- Action Methods
	void SetMaterialAlpha(float alpha) const;
	void ActivateFade();
	void DeActivateFade();

	void PermanentActivation();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bFading = false;
	bool bPermanentTurnedOn = false;

	UPROPERTY(EditAnywhere)
	TArray<UMeshComponent*> OwnerMesh;

	FTimeline FadeTimeLine;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UCurveFloat* FadeCurve;

	UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynamicMaterial;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void ObtainOwnerMaterial();
	
//---------------- TimeLine Methods
	void BindTimeLine();
	
	UFUNCTION()
	void FadeTick(float deltaSeconds);
	
	UFUNCTION()
	void FadeFinished();
};