//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

struct ObjectData
{
	FName nextLevelName;
};

UCLASS()
class THERITE_API AClock : public AInteractor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* Needles;

	UPROPERTY(EditAnywhere, Category= "Audio")
	USoundBase* Sound;

	UPROPERTY(EditAnywhere, Category= "Light")
	UPointLightComponent* Light;

	UPROPERTY(EditAnywhere, Category= "Settings")
	FName NextLevelName;
	
private:
	void ClockReady();

	//UPROPERTY(EditAnywhere, Category = "Rite Object")
	//ARite* TheRite;

protected:
	
	virtual void BeginPlay() override;

public:	
	AClock();
	~AClock();
	
	virtual void Interaction() override;

	FName GetObjectData();
};