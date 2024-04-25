//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RealWorldGameFlow.generated.h"

class ATriggerVolume;
class AAlex;
class UTutorialWidget;

UCLASS()
class THERITE_API ARealWorldGameFlow : public AActor
{
	GENERATED_BODY()
	
private:
	AAlex* Player;

	FTimerHandle ShowFirstTutorialWidget;
	FTimerHandle HideFirstTutorialWidget;
	FTimerHandle ShowSecondTutorialWidget;
	FTimerHandle HideSecondTutorialWidget;

	UTutorialWidget* FirstTutorialWidget;

	UPROPERTY(EditAnywhere, Category= "Widgets")
	TSubclassOf<UTutorialWidget> FirstTutorialMenu;
	
	UTutorialWidget* SecondTutorialWidget;

	UPROPERTY(EditAnywhere, Category= "Widgets")
	TSubclassOf<UTutorialWidget> SecondsTutorialMenu;
	
	//------------ In Level Varibles Objects
	UPROPERTY(EditAnywhere, Category= "Audios")
	USoundBase* FirstTalkAudio;
	
	UPROPERTY(EditAnywhere, Category= "Objects")
	ATriggerVolume* KnockTrigger;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_Knocking;
	
private:
	void CreateWidgets();
	
	
	void GetPlayer();
	
	UFUNCTION()
	void OnOverlapBeginKnock(AActor* OverlappedActor, AActor* OtherActor);


	void ShowingFirstTutorialWidget();
	void HidingFirstTutorialWidget();
	void ShowingSecondTutorialWidget();
	void HidingSecondTutorialWidget();

protected:
	virtual void BeginPlay() override;

public:	
	ARealWorldGameFlow();
};