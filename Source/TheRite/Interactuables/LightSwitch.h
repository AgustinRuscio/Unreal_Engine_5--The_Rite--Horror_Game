//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ALightSwitch();
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	virtual void Interaction() override;

	virtual void SetSpecialReady();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
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

	UPROPERTY(EditAnywhere, Category = "Lights")
	TArray<class ACustomLight*> CustomLightToInteract;

	FTimeline SwitchTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Time Line")
	UCurveFloat* EmptyCurve;
	
	UPROPERTY(EditAnywhere, Category = "Time Line")
	UCurveFloat* InvertedCurve;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
//---------------- TimeLine Methods
	void BindTimeLine();
	
	UFUNCTION()
	void SwitchTimeLineTick(float time);
	
	UFUNCTION()
	void SwitchTimeLineFinished();
};