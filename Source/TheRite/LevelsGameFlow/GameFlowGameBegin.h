//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheRite/Characters/Alex.h"
#include "GameFlowGameBegin.generated.h"

class ULevelSequence;
class UTutorialWidget;

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
	
	void ShowingFirstTutorialWidget();
	void ShowingSecondTutorialWidget();

private:
	//-------- TimeLines
	FTimerHandle ShowFirstTutorialWidget;
	FTimerHandle HideFirstTutorialWidget;
	FTimerHandle ShowSecondTutorialWidget;
	FTimerHandle HideSecondTutorialWidget;
	
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
	
	UPROPERTY(EditAnywhere, Category= "Sequence")
	ULevelSequence* LS_BeginSequence;

	AAlex* Player;
};