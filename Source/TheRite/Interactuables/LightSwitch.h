//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "LightSwitch.generated.h"

class ALightsTheRite;

UCLASS()
class THERITE_API ALightSwitch : public AInteractor
{
	GENERATED_BODY()

public:
	ALightSwitch();
	
//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction() override;

	virtual void SetSpecialReady();

private:
//---------------- TimeLine Methods
	void BindTimeLine();
	
	UFUNCTION()
	void SwitchTimeLineTick(float time);
	
	UFUNCTION()
	void SwitchTimeLineFinished();
	
private:	
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bOneUse = false;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bEspecial = false;
	
	bool bOneUseReady = false;
	
	bool bFlipFlop = false;
	
	UPROPERTY(EditAnywhere, Category = "State")
	bool bAnimReady = true;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* WallBlockModel;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* SwitchModel;
	
	UPROPERTY(EditAnywhere, Category = "Lights")
	TArray<ALightsTheRite*> LightToInteract;

	FTimeline SwitchTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Time Line")
	UCurveFloat* EmptyCurve;
	
	UPROPERTY(EditAnywhere, Category = "Time Line")
	UCurveFloat* InvertedCurve;
};