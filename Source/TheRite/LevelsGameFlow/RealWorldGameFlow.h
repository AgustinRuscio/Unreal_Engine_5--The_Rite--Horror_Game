//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RealWorldGameFlow.generated.h"

class ATriggerVolume;
class AAlex;

UCLASS()
class THERITE_API ARealWorldGameFlow : public AActor
{
	GENERATED_BODY()

public:
	ARealWorldGameFlow();

private:
	virtual void BeginPlay() override;
	
	void PlayerMethods();
	
//---------------- Widgets Methods
	void ShowingFirstTutorialWidget();
	void HidingFirstTutorialWidget();
	void ShowingSecondTutorialWidget();
	void HidingSecondTutorialWidget();
	
	UFUNCTION()
	void MainObjectGrabbed(class AInteractor* interactable);
	
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

	UPROPERTY(EditAnywhere, Category = "Audios")
	class AClock* Clock;

	UPROPERTY(EditAnywhere, Category = "Audios")
	TArray<USoundBase*> MainObjctGrabbedSound;
	
	AAlex* Player;
};