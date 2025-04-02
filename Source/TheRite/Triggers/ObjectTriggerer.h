//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectTriggerer.generated.h"

UCLASS()
class THERITE_API AObjectTriggerer : public AActor
{
	GENERATED_BODY()
	
public:
	virtual void Trigger();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = Settings)
	bool bReadyToTrigger;
};