//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActivateIntermitetntActorTrigger.generated.h"

UCLASS()
class THERITE_API AActivateIntermitetntActorTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AActivateIntermitetntActorTrigger();
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void Activate();
	void Deactivate();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category="Settings")
	bool bActive;

	UPROPERTY(EditAnywhere, Category = "Triggers", meta=(AllowPrivateAccess="true"))
	TArray<class AIntermitentActor*> IntermitentsActors;

	UPROPERTY(EditAnywhere, Category = "Triggers", meta=(AllowPrivateAccess="true"))
	class UBoxComponent* ActivateTrigger;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	UFUNCTION()
	void ActivateIntermitent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};