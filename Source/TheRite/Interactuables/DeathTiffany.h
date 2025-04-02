//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "TheRite/Interactuables/Interactor.h"
#include "DeathTiffany.generated.h"

UCLASS()
class THERITE_API ADeathTiffany : public AInteractor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ADeathTiffany();

	UPROPERTY(EditDefaultsOnly, Category = Visual, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BodyMesh; 

	UPROPERTY(EditDefaultsOnly, Category = Visual, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* PillowMesh; 

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void Interaction() override;

	void SetPillowReady(FString itemName, PickableItemsID id);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bHasPillow;

	FString PillowName;
	PickableItemsID PillowId;

	FVector PillowInitialLocation;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	USoundBase* PillowPlaced;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	USoundBase* NotReadyPillow;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	UAnimationAsset* DeathAnim;

	FTimeline PillowTimeLine;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	UCurveFloat* PillowCurveFloat;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void PillowTimeLineTick(float deltaSeconds);
	UFUNCTION()
	void PillowTimeLineFinish();
};