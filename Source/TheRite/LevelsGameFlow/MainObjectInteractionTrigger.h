//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainObjectInteractionTrigger.generated.h"

UCLASS()
class THERITE_API AMainObjectInteractionTrigger : public AActor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   // 
	//*****************************************************************************//
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   // 
	//*****************************************************************************//
	
	AMainObjectInteractionTrigger();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							...// 
	//*****************************************************************************//
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	class AClock* Clock;

	UPROPERTY(EditAnywhere, Category = "Audios")
	TArray<USoundBase*> MainObjctGrabbedSound;
		
	FTimerHandle WaitTimer;

	FTimerDelegate Del;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								...// 
	//*****************************************************************************//
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void MainObjectGrabbed(class AInteractor* interactable);
};