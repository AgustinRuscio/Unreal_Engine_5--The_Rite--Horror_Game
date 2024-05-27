//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FetusPuzzle.generated.h"

UCLASS()
class THERITE_API AFetusPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	AFetusPuzzle();
	
//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

public:	

private:
	
};