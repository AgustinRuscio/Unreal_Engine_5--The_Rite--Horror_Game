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

	TArray<class ALightsTheRite*> AllLights;

	
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void BindInteractables();

	UFUNCTION()
	void OnPuzzleFinished(class AInteractor* Interactable);
};