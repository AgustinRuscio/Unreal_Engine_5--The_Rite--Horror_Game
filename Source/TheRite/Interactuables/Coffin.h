//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Interactor.h"
#include "Coffin.generated.h"

UCLASS()
class THERITE_API ACoffin : public AInteractor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ACoffin();

	UPROPERTY(EditDefaultsOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CoffinMesh;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	void OpenCoffin();

private:	

	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bOpened;
	bool bFlipFlop;

	FVector CoffinOriginalLocation;
	FVector CoffinOpenedLocation;
	FVector CoffinClosedLocation;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector LocationToAddOpen;
	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector LocationToAddClosed;

	FTimeline CoffinMovementTimeLine;
	FTimeline CoffinClosedMovementTimeLine;

	UPROPERTY(EditDefaultsOnly, Category = "TimeLine")
	class UCurveFloat* TimeLineCurveFloat;

	UPROPERTY(EditDefaultsOnly, Category = "TimeLine")
	class UCurveFloat* TimeLineCloseCurveFloat;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	USoundBase* OpeningSound;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	USoundBase* ForceSound;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Interaction() override;

	UFUNCTION()
	void CoffinMovementTimeLineTick(float tick);
	UFUNCTION()
	void CoffinMovementTimeLineFinished();

	UFUNCTION()
	void CoffinClosedTimeLineTick(float tick);
	UFUNCTION()
	void CoffinClosedTimeLineFinished();
};