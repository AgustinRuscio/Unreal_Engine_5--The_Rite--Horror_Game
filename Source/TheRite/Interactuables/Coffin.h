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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFistOpening);

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
	USceneComponent* CoffinMCenter;

	UPROPERTY(EditDefaultsOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CoffinMattress;

	UPROPERTY(EditDefaultsOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CoffinDoor;

	UPROPERTY(EditDefaultsOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CoffinLatch;
	

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	FFistOpening CoffinOpening;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	bool IsCoffinOpen() const;

	void UnlockCoffin();

	void ForceCoffinOpenning();

private:	

	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bOpened;

	bool bIsOpen;
	bool bFlipFlop;

	bool bWasForceOpen;

	FRotator CoffinOriginalRotation;
	FRotator CoffinOpenedRotation;
	FRotator CoffinClosedRotation;

	FRotator CoffinLatchOriginalRotation;
	FRotator CoffinLatchOpenedRotation;
	FRotator CoffinLatchClosedRotation;

	FVector CoffinMattressOriginalRotation;
	FVector CoffinMattressOpenedRotation;
	FVector CoffinMattressClosedRotation;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FRotator RotationToAddOpen;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FRotator RotationToAddClosed;


		UPROPERTY(EditAnywhere, Category = "Settings")
	FRotator RotationLatchToAddOpen;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FRotator RotationLatchToAddClosed;


	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector LocationToAddMatrresOpen;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector LocationToAddMatrresClosed;


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

	void BindTimeLineMethods();
	void SaveLocationAndRotation();

	UFUNCTION()
	void CoffinMovementTimeLineTick(float tick);
	UFUNCTION()
	void CoffinMovementTimeLineFinished();

	UFUNCTION()
	void CoffinClosedTimeLineTick(float tick);
	UFUNCTION()
	void CoffinClosedTimeLineFinished();

	void LerpValues(const FRotator& DoorRotation, const FRotator& LatchRotation, const FVector& MattressLocation);
};