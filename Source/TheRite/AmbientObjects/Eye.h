//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Eye.generated.h"

UCLASS()
class THERITE_API AEye : public AActor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AEye();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	FVector TargetPosition;
	
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void Tick(float DeltaTime) override;
};