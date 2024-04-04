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

private:

	UPROPERTY(EditAnywhere, Category= "AI behaviour")
	UBehaviorTree* BehaviourTree;
	
protected:
	
	virtual void BeginPlay() override;

public:
	UBehaviorTree* GetBehaviourTree() const;
};