#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Rite.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

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
	
private:
	void ClockReady();

	UPROPERTY(EditAnywhere, Category = "Rite Object")
	ARite* TheRite;

protected:
	
	virtual void BeginPlay() override;

public:	
	AClock();
	
	virtual void Interaction() override;
	
};