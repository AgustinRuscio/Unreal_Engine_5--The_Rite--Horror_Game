//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	ADoorKey();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Mesh")
	UStaticMeshComponent* KeyMesh;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnKeyCollected OnKeyCollected;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	virtual void Interaction() override;
	
	void SetDoor(ADoor* NewDoor);
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category= "States")
	bool bKeyReady;
	
	UPROPERTY(EditAnywhere, Category= "Light")
	UPointLightComponent* PointLight;

	UPROPERTY(EditAnywhere, Category= "Audio")
	USoundBase* VoiceSound;

	UPROPERTY(EditAnywhere, Category= "My Door")
	ADoor* MyDoor;
};