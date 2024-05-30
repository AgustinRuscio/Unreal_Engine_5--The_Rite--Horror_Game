//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once
#include "CoreMinimal.h"
#include "FetusPuzzle.h"
#include "GameFramework/Actor.h"
#include "GameFlowPacifierLevel.generated.h"

class ARectLight;
class ATriggerVolume;
class ALightsTheRite;
class ALightSwitch;
class ALadder;
class ADoor;

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
	
public:
	
private:
	bool bLightsOutEventDone;

	UPROPERTY(EditAnywhere, Category= "Settiings")
	float EmergencyLightsIntensity = 25.f;
	
//-------- Colliders
	UPROPERTY(EditAnywhere, Category= "Triggers")
	ATriggerVolume* TriggerVolume_LightsOut;

//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_LightsOut;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_PowerDowns;

//-------- Lights
	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ALightsTheRite*> Lights_AllLights;

	UPROPERTY(EditAnywhere, Category="Lights")
	TArray<ARectLight*> EmergencyLights;

	UPROPERTY(EditAnywhere, Category="Flows")
	AFetusPuzzle* GameFlow_FetusPuzzle;

	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_BedRoom;
	
	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_BathRoomRoom;
	
	UPROPERTY(EditAnywhere, Category="Light Switch")
	ALightSwitch* LightSwitch_TermicalSwitch;

	UPROPERTY(EditAnywhere, Category="Objects")
	ALadder* AtticLader;
};