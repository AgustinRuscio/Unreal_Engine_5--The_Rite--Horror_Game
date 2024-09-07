//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

class UPointLightComponent;

UCLASS()
class THERITE_API AClock : public AInteractor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   // 
	//*****************************************************************************//

	//Constructor
	AClock();
	~AClock();
	
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* Needles;
	
	UPROPERTY(EditAnywhere, Category= "Light")
	UPointLightComponent* Light;
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   // 
	//*****************************************************************************//
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   // 
	//*****************************************************************************//
	FName GetObjectData() const;
	
	virtual void Interaction() override;

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							...// 
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = Settings)
	bool bTest;

	UPROPERTY(EditAnywhere, Category = Settings)
	float MinimumDistanceForPostProces;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	FName NextLevelName;
	
	FName PostProcessModiferValue = "SpectralProximity";

	UPROPERTY(EditAnywhere, Category= "Light")
	TArray<class ALightsTheRite*> TurnedOfLights;
	
	UPROPERTY(EditAnywhere, Category= "Light")
	TArray<class ACandle*> ObjCandles;

	UPROPERTY(EditAnywhere, Category= "FeedBack")
	class AProsProcessModifier* PostProcesModifierClass;

	class AAlex* Player;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								...// 
	//*****************************************************************************//
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void CalculateDistanceWithPlayer();
};