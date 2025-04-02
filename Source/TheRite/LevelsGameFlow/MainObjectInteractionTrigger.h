//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AMainObjectInteractionTrigger();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							...// 
	//*****************************************************************************//
	FName GameName;

	UPROPERTY(EditAnywhere, Category = "Audios")
	class AClock* Clock;

	UPROPERTY(EditAnywhere, Category = "Audios")
	TArray<USoundBase*> MainObjctGrabbedSound;
		
	FTimerHandle WaitTimer;

	//*****************************************************************************//
	//								PRIVATE METHODS								...// 
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OpenLevel();
	
	UFUNCTION()
	void MainObjectGrabbed(class AInteractor* interactable);
};