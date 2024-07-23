//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Clock.h"
#include "GameFlowGameBegin.generated.h"

class ULevelSequence;
class UTutorialWidget;
class AAlex;
class ARite;
class ATiffany;
class ALightsTheRite;
class ANiagaraActor;

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
	void OnRiteInteraction(AInteractor* Interactor);
	
	void ShowingFirstTutorialWidget();
	void ShowingSecondTutorialWidget();

private:
	
	UPROPERTY(EditAnywhere, Category="Settings")
	FName NextLevel;
	
	//-------- TimeLines
	FTimerHandle ShowFirstTutorialWidget;
	FTimerHandle HideFirstTutorialWidget;
	FTimerHandle ShowSecondTutorialWidget;
	FTimerHandle HideSecondTutorialWidget;
	
	//-------- Widgets
	UPROPERTY(EditAnywhere, Category= "Settings")
	ULevelSequence* LS_BeginSequence;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	ULevelSequence* LS_RiteSequence;

	UPROPERTY(EditAnywhere, Category= "Settings")
	ANiagaraActor* Fog;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	ARite* Rite;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	TArray<AClock*> MainItems;
	
	UPROPERTY(EditAnywhere, Category= "Widgets")
	TSubclassOf<UTutorialWidget> FirstTutorialMenu;
	UTutorialWidget* FirstTutorialWidget;

	UPROPERTY(EditAnywhere, Category= "Widgets")
	TSubclassOf<UTutorialWidget> SecondsTutorialMenu;
	UTutorialWidget* SecondTutorialWidget;

	UPROPERTY(EditAnywhere, Category= "Widgets")
	TSubclassOf<UTutorialWidget> FindObjectsMenu;
	UTutorialWidget* FindObjectsMenuWidget;


	UPROPERTY(EditAnywhere, Category= "Lights")
	TArray<ALightsTheRite*> Lights_Garage;

	UPROPERTY(EditAnywhere, Category= "Lights")
	ATiffany* Tiffany_Garage;
	
	AAlex* Player;
};