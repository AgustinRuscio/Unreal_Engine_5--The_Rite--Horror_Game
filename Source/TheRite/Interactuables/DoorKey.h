#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "Interactor.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Widgets/KeyWidget.h"
#include "DoorKey.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKeyCollected);

UCLASS()
class THERITE_API ADoorKey : public AInteractor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* KeyMesh;

	UPROPERTY(EditAnywhere, Category= "Light")
	UPointLightComponent* PointLight;
	
	UPROPERTY(EditAnywhere, Category= "UI")
	TSubclassOf<UKeyWidget> KeyUI;
	
	UKeyWidget* KeyWidget;

	UPROPERTY(EditAnywhere, Category= "Zone Name")
	FString DoorZoneName;

	UPROPERTY(EditAnywhere, Category= "Audio")
	USoundBase* VoiceSound;
	
	UPROPERTY(EditAnywhere, Category= "Audio")
	USoundBase* SFXGrabItem;

	UPROPERTY(EditAnywhere, Category= "My Door")
	ADoor* MyDoor;

	UPROPERTY(EditAnywhere, Category= "States")
	bool bKeyReady;

	FTimerHandle timer;

	void TimeOver();
	
protected:
	virtual void BeginPlay() override;

public:	
	ADoorKey();
	virtual void Interaction() override;

	FOnKeyCollected OnKeyCollected;
};
