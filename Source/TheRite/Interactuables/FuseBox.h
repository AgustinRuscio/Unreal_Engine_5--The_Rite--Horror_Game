//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FuseBox.generated.h"

UCLASS()
class THERITE_API AFuseBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AFuseBox();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:	

};