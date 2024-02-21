#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "LoreInteractuable.generated.h"

UCLASS()
class THERITE_API ALoreInteractuable : public AInteractor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* BaseMesh;

public:	
	ALoreInteractuable();
	
	virtual void Interaction() override;
};