//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "DoorKey.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKeyCollected);


class UPointLightComponent;
class ADoor;

UCLASS()
class THERITE_API ADoorKey : public AInteractor
{
	GENERATED_BODY()

public:
	ADoorKey();
	
	virtual void Interaction() override;
	
	void SetDoor(ADoor* NewDoor);

public:	
	FOnKeyCollected OnKeyCollected;
	
private:
	UPROPERTY(EditAnywhere, Category= "States")
	bool bKeyReady;
	
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* KeyMesh;

	UPROPERTY(EditAnywhere, Category= "Light")
	UPointLightComponent* PointLight;

	UPROPERTY(EditAnywhere, Category= "Audio")
	USoundBase* VoiceSound;

	UPROPERTY(EditAnywhere, Category= "My Door")
	ADoor* MyDoor;
};