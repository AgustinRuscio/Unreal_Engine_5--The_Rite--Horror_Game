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

public:
	ARealWorldGameFlow();
	virtual void BeginPlay() override;

private:
	void PlayerMethods();
	
//---------------- Widgets Methods
	void CreateWidgets();
	void ShowingFirstTutorialWidget();
	void HidingFirstTutorialWidget();
	void ShowingSecondTutorialWidget();
	void HidingSecondTutorialWidget();
	
	UFUNCTION()
	void OnOverlapBeginKnock(AActor* OverlappedActor, AActor* OtherActor);
	
private:
	//-------- Collider
	UPROPERTY(EditAnywhere, Category= "Objects")
	ATriggerVolume* KnockTrigger;
	
	//-------- Audio
	UPROPERTY(EditAnywhere, Category= "Audios")
	USoundBase* FirstTalkAudio;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_Knocking;
	
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

	
	AAlex* Player;
};