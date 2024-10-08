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
	class ATriggerBox* TriggerEnableManikin;
	
	UPROPERTY(EditAnywhere, Category = "Triggers", meta = (AllowPrivateAccess = "true"))
	class ATriggerBox* TriggerEnd;
	
	UPROPERTY(EditAnywhere, Category = "Triggers", meta = (AllowPrivateAccess = "true"))
	class ATriggerBox* TriggerOutSideEnd;
	
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
	bool bPuzzleEnd;
	
	UPROPERTY(EditAnywhere, Category = Interactables)
	class AInteractor* EndInteractable;

	//UPROPERTY(EditAnywhere, Category = Doors)
	//TArray<class ADoor*> InitialDoors;
	
	UPROPERTY(EditAnywhere, Category = Doors)
	TArray<class ADoor*> RoomsDoors;

	UPROPERTY(EditAnywhere, Category = Doors)
	TArray<class ADoor*> InitialDoors;
	
	UPROPERTY(EditAnywhere, Category = Lights)
	TArray<class ALightsTheRite*> AllLights;

	UPROPERTY(EditAnywhere, Category = Triggers)
	class ADoorSlapper* DoorSlapperHangedMan;

	UPROPERTY(EditAnywhere, Category = Triggers)
	class ATriggererObject* TriggererObjectWheelChair;
	
	UPROPERTY(EditAnywhere, Category = Ambient)
	class AManikin* Manikin;

	UPROPERTY(EditAnywhere, Category = Ambient)
	class ATimerSound* TimerSound;
	
	UPROPERTY(EditAnywhere, Category = Ambient)
	class ASkeletalMeshActor* EndTiffany;

	UPROPERTY(EditAnywhere, Category = Ambient)
	TArray<class AStaticMeshActor*> PuzzleWalls;

	UPROPERTY(EditAnywhere, Category = Ambient)
	class AFetchInOrderPuzzle* FetchPuzzle;
	
	FTimerHandle TimerHandleEnd;
	
	FTimerDelegate TimerDelegateEnd;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void BindInteractables();
	void BindTriggers();
	
	UFUNCTION()
	void OnFetchPuzzleStarted(class AInteractor* Interactable);
	UFUNCTION()
	void OnFetchPuzzleFinished();
	

	UFUNCTION()
	void OnTriggerBeginEnableAmbientInteractions(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerBeginEnd(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerBeginOutSideEnd(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerBeginDoorSlapperHangedMan();
};