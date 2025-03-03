//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MorguePuzzleFlow.generated.h"

UCLASS()
class THERITE_API AMorguePuzzleFlow : public AActor
{
	GENERATED_BODY()
	


public:

	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AMorguePuzzleFlow();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Settings)
	class AInteractor* Emblem;

	UPROPERTY(EditAnywhere, Category = Settings)
	class AStaticMeshActor* DeadBodyOne;

	UPROPERTY(EditAnywhere, Category = Settings)
	class AStaticMeshActor* DeadBodyTwo;

	UPROPERTY(EditAnywhere, Category = Settings)
	class ATargetPoint* DeadBodyOneTargetPoint;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	class ATargetPoint* DeadBodyTwoTargetPoint;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEmblemInteraction(class AInteractor* interactor);
};