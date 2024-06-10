//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once
#include "CoreMinimal.h"
#include "FetusPuzzle.h"
#include "GameFramework/Actor.h"
#include "TheRite/AmbientObjects/Candle.h"
#include "GameFlowPacifierLevel.generated.h"

class ARectLight;
class ATriggerVolume;
class ALightsTheRite;
class ALightSwitch;
class ALadder;
class ADoor;
class AEmergencyLights;

UCLASS()
class THERITE_API AGameFlowPacifierLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameFlowPacifierLevel();

//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnLightsOnEvent(AInteractor* Interactor);
	
	UFUNCTION()
	void EndGame();
	
//---------------- Bind Colliders Methods
	void BindColliderMethods();
	
	UFUNCTION()
	void OnTriggerLightsOutEventOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnTriggerEndGamePassOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
public:
	
private:
	bool bLightsOutEventDone;

	bool bEndGamePassDone = false;
	
	UPROPERTY(EditAnywhere, Category= "Settiings")
	float EmergencyLightsIntensity = 25.f;
	
//-------- Colliders
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_LightsOut;
	
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_EndGmaePass;

//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_LightsOut;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_PowerDowns;

	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_PowerRestored;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_EndGame;

//-------- Lights
	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ALightsTheRite*> Lights_AllLights;

	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ACandle*> Candles_EndGame;

//-------- Doors
	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_BedRoom;

	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_EndGame;
	
	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_BathRoomRoom;
	
//-------- Flows & Puzzles
	UPROPERTY(EditAnywhere, Category="Flows")
	AFetusPuzzle* GameFlow_FetusPuzzle;
	
	UPROPERTY(EditAnywhere, Category="Light Switch")
	ALightSwitch* LightSwitch_TermicalSwitch;

	UPROPERTY(EditAnywhere, Category="Objects")
	ALadder* AtticLader;
	
	UPROPERTY(EditAnywhere, Category="Light")
	TArray<AEmergencyLights*> EmergencyLights;
};