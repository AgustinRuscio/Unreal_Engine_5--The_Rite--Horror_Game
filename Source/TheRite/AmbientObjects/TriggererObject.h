//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggererObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggererObjectEvent);

UCLASS()
class THERITE_API ATriggererObject : public AActor
{
	GENERATED_BODY()

	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ATriggererObject();
	
	UPROPERTY(EditAnywhere, Category = "Triggers", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Trigger;
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnTriggererObjectEvent OnTriggererObjectEvent;
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	bool ActiveState() const;
	
	void Activate();
	void Deactivate();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = Settings)
	bool bActive = true;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	TArray<class AObjectTriggerer*> TriggererObjects;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTriggerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};