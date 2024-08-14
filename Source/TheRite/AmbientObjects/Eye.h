//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Eye.generated.h"

UCLASS()
class THERITE_API AEye : public AActor
{
	GENERATED_BODY()
	
public:
	AEye();

private:
	virtual void Tick(float DeltaTime) override;
	
private:
	FVector TargetPosition;
	
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* StaticMeshComponent;
};