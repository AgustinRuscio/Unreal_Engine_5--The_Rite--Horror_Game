//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TiffanyController.generated.h"

UCLASS()
class THERITE_API ATiffanyController : public AAIController
{
	GENERATED_BODY()

public:
	ATiffanyController();

	UBehaviorTree* GetBehaviourTree() const;

private:
	UPROPERTY(EditAnywhere, Category= "AI behaviour")
	UBehaviorTree* BehaviourTree;

	virtual void BeginPlay() override;
};