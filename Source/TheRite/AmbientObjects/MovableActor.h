//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Triggers/ObjectTriggerer.h"
#include "MovableActor.generated.h"

UCLASS()
class THERITE_API AMovableActor : public AObjectTriggerer
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AMovableActor();

	UPROPERTY(EditDefaultsOnly, Category = Visuals, meta = (allowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = Visuals, meta = (allowPrivateAccess = "true"))
	class UAudioComponent* AudioComponent;
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	virtual void Trigger() override;
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bForce;

	UPROPERTY(EditAnywhere, Category = Settings)
	FVector ForceDirection;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	class ATargetPoint* EndLocation;

	UPROPERTY(EditAnywhere, Category = Lights)
	TArray<class ALightsTheRite*> NearLights;

	UPROPERTY(EditAnywhere, Category = Settings)
	TArray<class ACustomLight*> NearLights2;
	
	UPROPERTY(EditAnywhere, Category = SFX)
	USoundBase* SFX_Movement;
	
	UPROPERTY(EditAnywhere, Category = SFX)
	USoundBase* SFX_MovementFinished;
	
	FTimeline MoveTimeLine;
	
	UPROPERTY(EditAnywhere, Category = TimeLine)
	UCurveFloat* CurveFloat;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void PlayBeginFeedBack();
	void PlayEndFeedBack();
	
	UFUNCTION()
	void OnMovingTick(float DeltaTime);
	
	UFUNCTION()
	void OnMovementFinished();
};