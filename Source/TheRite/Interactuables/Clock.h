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
	AClock();
	~AClock();
	
	FName GetObjectData() const;
	
	virtual void Interaction() override;

private:

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bTest;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	FName NextLevelName;
	
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* Needles;

	UPROPERTY(EditAnywhere, Category= "Light")
	UPointLightComponent* Light;

	UPROPERTY(EditAnywhere, Category= "Light")
	TArray<class ALightsTheRite*> TurnedOfLights;
	
	UPROPERTY(EditAnywhere, Category= "Light")
	TArray<class ACandle*> ObjCandles;
};