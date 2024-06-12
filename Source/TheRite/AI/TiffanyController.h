//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TiffanyController.generated.h"

UCLASS()
class THERITE_API ATiffanyController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UBehaviorTree* GetBehaviourTree() const;

private:
	UPROPERTY(EditAnywhere, Category= "AI behaviour")
	UBehaviorTree* BehaviourTree;
};