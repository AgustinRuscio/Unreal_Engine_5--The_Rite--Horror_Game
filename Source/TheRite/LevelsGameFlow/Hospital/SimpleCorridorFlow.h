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

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComp;
	
	UPROPERTY(EditAnywhere, Category = "Triggers", meta = (AllowPrivateAccess = "true"))
	class ATriggerBox* TriggerEnableManikin;
	
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
	
	FName PostProcessModiferValue = "SpectralProximity";
	
	UPROPERTY(EditAnywhere, Category = Interactables)
	class AInteractor* EndInteractable;

	//UPROPERTY(EditAnywhere, Category = Doors)
	//TArray<class ADoor*> InitialDoors;
	
	//----- Doors
	UPROPERTY(EditAnywhere, Category = Doors)
	TArray<class ADoor*> RoomsDoors;

	UPROPERTY(EditAnywhere, Category = Doors)
	TArray<class ADoor*> InitialDoors;
	
	UPROPERTY(EditAnywhere, Category = Doors)
	TArray<class ADoor*> SecondPuzzleDoors;

	//----- Triggers
	UPROPERTY(EditAnywhere, Category = Lights)
	TArray<class ALightsTheRite*> AllLights;

	UPROPERTY(EditAnywhere, Category = Triggers)
	class ADoorScaryKnocking* DoorSlapperHangedMan;

	UPROPERTY(EditAnywhere, Category = Triggers)
	class ATriggererObject* TriggererObjectWheelChair;

	UPROPERTY(EditAnywhere, Category = Triggers)
	class ABackCorridorFlow* NextPuzzle;
	
	//----- Ambient
	UPROPERTY(EditAnywhere, Category = Ambient)
	class AManikin* Manikin;

	UPROPERTY(EditAnywhere, Category = Ambient)
	class ATimerSound* TimerSound;

	UPROPERTY(EditAnywhere, Category = Ambient)
	TArray<class AStaticMeshActor*> PuzzleWalls;

	UPROPERTY(EditAnywhere, Category = Ambient)
	class AFetchInOrderPuzzle* FetchPuzzle;

	//----- Audios
	UPROPERTY(EditAnywhere, Category = Audios)
	TArray<class AAmbientSound*>  AmbientSoundsOnPuzzle;
	
	UPROPERTY(EditAnywhere, Category = Audios)
	class AAmbientSound*  SFX_PuzzleClueLocation;

	UPROPERTY(EditAnywhere, Category = Audios)
	class USoundBase* ZoneCompleted;

	//---- Feed back

	UPROPERTY(EditAnywhere, Category = Lights)
	class ASpotLight* HintSpotlight;
	
	UPROPERTY(EditAnywhere, Category = FeedBack, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShake_Puzzle;
	
	UPROPERTY(EditAnywhere, Category = FeedBack)
	class AProsProcessModifier* PostProcessModifier;

	UPROPERTY(EditAnywhere, Category = FeedBack)
	TArray<class ACyclicAudios*> CyclicAudios;

	UPROPERTY(EditAnywhere, Category = FeedBack)
	class AInteractor* AppearanceInteractable;
	
	UPROPERTY(EditAnywhere, Category = FeedBack)
	class AAppearanceEvent* HangedManAppearance;

	UPROPERTY(EditAnywhere, Category = Obj)
	TWeakObjectPtr<class AInteractor> Emblem;

	UPROPERTY(EditAnywhere, Category = Obj)
	TWeakObjectPtr<class AWalkerTiffany> Walker;
	
	//---- Timers
	FTimerHandle TimerHandleEnd;
	FTimerDelegate TimerDelegateEnd;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void BindInteractables();
	void BindTriggers();

	UFUNCTION()
	void ActivateWalk(class AInteractor* interactor);

	UFUNCTION()
	void CallBackForAppearanceEvent(class AInteractor* interactor);
	
	UFUNCTION()
	void LightsOn();
	
	UFUNCTION()
	void LightsOff();
	
	UFUNCTION()
	void OnFetchPuzzleStarted(class AInteractor* Interactable);
	
	UFUNCTION()
	void OnFetchPuzzleFinished();

	void PuzzleFeedBack(bool bFeedBackOn);

	UFUNCTION()
	void OnTriggerBeginEnableAmbientInteractions(AActor* OverlappedActor, AActor* OtherActor);
	
	
	UFUNCTION()
	void OnTriggerBeginOutSideEnd(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnTriggerBeginDoorSlapperHangedMan();
};