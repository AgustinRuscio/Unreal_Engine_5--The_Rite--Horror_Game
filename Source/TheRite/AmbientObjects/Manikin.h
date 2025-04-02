//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "Manikin.generated.h"

UCLASS()
class THERITE_API AManikin : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	AManikin();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void Activate();
	void Deactivate();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category="Settings")
	bool bStartsActive;
	bool bActive;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	float ReLocateColdDown;
	float ReLocateTimer;
	
	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="Target points")
	TArray<ATargetPoint*> PossiblesLocations;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void Tick(float DeltaTime) override;
	
	void ReLocateObject();
};