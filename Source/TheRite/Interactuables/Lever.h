//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//
#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Lever.generated.h"

UCLASS()
class THERITE_API ALever : public AInteractor
{
	GENERATED_BODY()

public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ALever();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Visual, meta = (allowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Visual, meta = (allowPrivateAccess = "true"))
	class UPointLightComponent* PointLight;
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	virtual void Interaction() override;

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bIsCorrect;

	
	FTimeline Timeline;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	UCurveFloat* CurveFloat;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void LeverTimeLineTick(float delta);

	UFUNCTION()
	void LeverTimeLineFinished();
	
	void ResetLever();
};