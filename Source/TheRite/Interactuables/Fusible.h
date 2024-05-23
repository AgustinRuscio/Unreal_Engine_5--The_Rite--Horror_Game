//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fusible.generated.h"

UCLASS()
class THERITE_API AFusible : public AActor
{
	GENERATED_BODY()
	
public:	
	AFusible();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	

};