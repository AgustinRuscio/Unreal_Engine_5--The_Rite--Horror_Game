//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFlowGameBegin.generated.h"

UCLASS()
class THERITE_API AGameFlowGameBegin : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameFlowGameBegin();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};