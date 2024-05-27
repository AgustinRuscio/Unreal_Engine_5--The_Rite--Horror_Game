//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Door.h"
#include "GameFlowPacifierLevel.generated.h"

class ASpotLight;
class ATriggerVolume;
class ALightsTheRite;
class ALightSwitch;
class ALadder;

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
	
//---------------- Bind Colliders Methods
	void BindColliderMethods();
	
	UFUNCTION()
	void OnTriggerLightsOutEventOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
public:
	
private:
	bool bLightsOutEventDone;
	
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
	TArray<ASpotLight*> EmergencyLights;


	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_BedRoom;
	
	UPROPERTY(EditAnywhere, Category="Doors")
	ADoor* Door_BathRoomRoom;
	
	UPROPERTY(EditAnywhere, Category="Light Switch")
	ALightSwitch* LightSwitch_TermicalSwitch;

	UPROPERTY(EditAnywhere, Category="Objects")
	ALadder* AtticLader;
};