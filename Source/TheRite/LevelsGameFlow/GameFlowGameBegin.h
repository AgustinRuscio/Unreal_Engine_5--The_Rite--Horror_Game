//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFlowGameBegin.generated.h"

class AInteractor;
class ULevelSequence;
class UTutorialWidget;
class AAlex;
class ARite;
class ATiffany;
class ALightsTheRite;
class ANiagaraActor;
class AClock;
class ACandle;
class ALighter;
class AStaticMeshActor;

UCLASS()
class THERITE_API AGameFlowGameBegin : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameFlowGameBegin();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetNeededValues();
	void CreateWidgets();
	
	void PlayBeginSequence();
	
	UFUNCTION()
	void BeginSequenceFinished();

	void PlayRiteSequence();

	UFUNCTION()
	void RiteSequenceFinished();
	
	UFUNCTION()
	void OnRiteInteraction(AInteractor* Interactable);

	UFUNCTION()
	void OnRiteReady();
	
	UFUNCTION()
	void OnRiteObjetObtain(AInteractor* Interactable);
	
	void ShowingFirstTutorialWidget();
	void ShowingSecondTutorialWidget();

private:
	
	UPROPERTY(EditAnywhere, Category="Settings")
	FName NextLevel;

	//-------- Meshes
	UPROPERTY(EditAnywhere, Category="Rite Meshes")
	AStaticMeshActor* RiteMesh_Clock;
	
	UPROPERTY(EditAnywhere, Category="Rite Meshes")
	AStaticMeshActor* RiteMesh_Diary;
	
	UPROPERTY(EditAnywhere, Category="Rite Meshes")
	AStaticMeshActor* RiteMesh_Pacifier;
	
	//-------- TimeLines
	FTimerHandle ShowFirstTutorialWidget;
	FTimerHandle HideFirstTutorialWidget;
	FTimerHandle ShowSecondTutorialWidget;
	FTimerHandle HideSecondTutorialWidget;

	//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SFX_Clue;
	
	//-------- Sequence
	UPROPERTY(EditAnywhere, Category= "Settings")
	ULevelSequence* LS_BeginSequence;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	ULevelSequence* LS_RiteSequence;
	
	//-------- Widgets
	UPROPERTY(EditAnywhere, Category= "Widgets")
	TSubclassOf<UTutorialWidget> FirstTutorialMenu;
	UTutorialWidget* FirstTutorialWidget;

	UPROPERTY(EditAnywhere, Category= "Widgets")
	TSubclassOf<UTutorialWidget> SecondsTutorialMenu;
	UTutorialWidget* SecondTutorialWidget;

	UPROPERTY(EditAnywhere, Category= "Widgets")
	TSubclassOf<UTutorialWidget> FindObjectsMenu;
	UTutorialWidget* FindObjectsMenuWidget;
	
	//-------- In game obejcts
	UPROPERTY(EditAnywhere, Category= "Settings")
	ANiagaraActor* Fog;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	ARite* Rite;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	TArray<AClock*> MainItems;

	UPROPERTY(EditAnywhere, Category= "Lights")
	TArray<ACandle*> CandlesGuidance;
	
	UPROPERTY(EditAnywhere, Category= "Lights")
	TArray<ALightsTheRite*> AllLights;

	UPROPERTY(EditAnywhere, Category= "Settings")
	ATiffany* Tiffany_Garage;

	UPROPERTY(EditAnywhere, Category= "Settings")
	ALighter* Lighter;
	
	AAlex* Player;
};