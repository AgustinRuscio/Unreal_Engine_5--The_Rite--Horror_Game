//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "GameFlowDiaryLevelOtherWorld.generated.h"

class AInOrdenSelectionPuzzleFlow;
class ATriggerBox;
class ASpotLight;
class AAlex;
class ADoor;

UCLASS()
class THERITE_API AGameFlowDiaryLevelOtherWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameFlowDiaryLevelOtherWorld();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void EndGame();

	void BindTriggers();
	void BindMethods();
	void InitializeValues();
	
public:	

private:

	UPROPERTY(EditAnywhere, Category = "Ambient Audios")
	USoundBase* SFX_LastAudio;
	UPROPERTY(EditAnywhere, Category = "Ambient Audios")
	USoundBase* SFX_LightsOut;

	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ALightsTheRite*> InGameLights;

	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ASpotLight*> Lights_SpotLightEndGame;
	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ASpotLight*> Lights_Altar;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	AInOrdenSelectionPuzzleFlow* InOrderPOuzzleController;

	UPROPERTY(EditAnywhere, Category= "Doors")
	
	ADoor* Doors_BathRoom;
	UPROPERTY(EditAnywhere, Category= "Doors")
	
	ADoor* Doors_BedRoom;
	UPROPERTY(EditAnywhere, Category= "Doors")
	ADoor* Doors_EndGame;

	AAlex* Player;
};
