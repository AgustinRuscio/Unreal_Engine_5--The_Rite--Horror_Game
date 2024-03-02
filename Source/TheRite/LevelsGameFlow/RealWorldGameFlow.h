#pragma once

#include "CoreMinimal.h"
#include "Engine/SpotLight.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "TheRite/AmbientObjects/Candle.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Characters/Tiffany.h"
#include "TheRite/Interactuables/LockedDoor.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "RealWorldGameFlow.generated.h"

UCLASS()
class THERITE_API ARealWorldGameFlow : public AActor
{
	GENERATED_BODY()
	
private:
	AAlex* Player;

	FTimeline OnCloseTimeline;


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
	
	UPROPERTY(EditAnywhere, Category= "Audios")
	USoundBase* ReactToLockedDoorAudio;
	
	UPROPERTY(EditAnywhere, Category= "Audios")
	USoundBase* SFX_SlamDoor;
	
	UPROPERTY(EditAnywhere, Category= "Audios")
	USoundBase* SFX_DoorOpening;

	
	UPROPERTY(EditAnywhere, Category= "Objects")
	ALockedDoor* LockedInteractionDoor;
	
	UPROPERTY(EditAnywhere, Category= "Objects")
	ADoor* ArtRoomDoor;

	UPROPERTY(EditAnywhere, Category= "Objects")
	TArray<ASpotLight*> ArtRoomRedLights;

	UPROPERTY(EditAnywhere, Category= "Objects")
	ATriggerVolume* SlamDoorTriggerVolume;
	
	UPROPERTY(EditAnywhere, Category= "Objects")
	ATriggerVolume* KnockTrigger;
	
	UPROPERTY(EditAnywhere, Category= "Objects")
	ATiffany* ArtRoomTiffany;
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_Knocking;

	UPROPERTY(EditAnywhere, Category= "Objects")
	float OnCloseTimeLineLength = 0.2f;

	bool bCloseDoor = false;

	int DoOnce = 0;

	
private:
void CreateWidgets();
	
	UFUNCTION()
	void OpenArtRoomDoor();
	
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnCloseTimeLineFinished();

	void BindTimeLine();
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
	virtual void Tick(float DeltaTime) override;

};