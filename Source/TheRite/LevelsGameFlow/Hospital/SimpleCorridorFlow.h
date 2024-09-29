//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleCorridorFlow.generated.h"

UCLASS()
class THERITE_API ASimpleCorridorFlow : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ASimpleCorridorFlow();

	UPROPERTY(EditAnywhere, Category = "Triggers", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TriggerEnableManikin;
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Interactables)
	class AInteractor* EndInteractable;

	UPROPERTY(EditAnywhere, Category = Doors)
	TArray<class ADoor*> InitialDoors;
	 
	UPROPERTY(EditAnywhere, Category = Doors)
	TArray<class ADoor*> RoomsDoors;

	UPROPERTY(EditAnywhere, Category = Lights)
	TArray<class ALightsTheRite*> AllLights;

	UPROPERTY(EditAnywhere, Category = Ambient)
	class AManikin* Manikin;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void BindInteractables();

	UFUNCTION()
	void OnTriggerBeginEnableManikin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnPuzzleFinished(class AInteractor* Interactable);
};