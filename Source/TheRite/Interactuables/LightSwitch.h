//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "LightSwitch.generated.h"

UCLASS()
class THERITE_API ALightSwitch : public AInteractor
{
	GENERATED_BODY()
	
private:	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* WallBlockModel;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* SwitchModel;
	
	UPROPERTY(EditAnywhere, Category = "Lights")
	TArray<ALightsTheRite*> LightToInteract;

	FTimeline SwitchTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Time Line")
	UCurveFloat* EmptyCurve;
	
	bool bFlipFlop = false;
	
	UPROPERTY(EditAnywhere, Category = "State")
	bool bAnimReady = true;

	UFUNCTION()
	void SwitchTimeLineTick(float time);
	UFUNCTION()
	void SwitchTimeLineFinished();
	
protected:
	virtual void BeginPlay() override;

public:	
	ALightSwitch();
	
	virtual void Tick(float DeltaTime) override;

	virtual void Interaction() override;
	
};