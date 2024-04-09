//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "TheRite/Characters/Alex.h"
#include "GameFramework/Actor.h"
#include "TransitionWorldFlow.generated.h"

UCLASS()
class THERITE_API ATransitionWorldFlow : public AActor
{
	GENERATED_BODY()
	
private:	

	AAlex* Player;
	
protected:
	virtual void BeginPlay() override;

public:	
	ATransitionWorldFlow();
};