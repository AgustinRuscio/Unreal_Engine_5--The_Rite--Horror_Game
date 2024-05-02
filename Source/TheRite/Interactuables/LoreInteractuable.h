//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "LoreInteractuable.generated.h"

UCLASS()
class THERITE_API ALoreInteractuable : public AInteractor
{
	GENERATED_BODY()

public:	
	ALoreInteractuable();
	
	virtual void Interaction() override;
	
private:
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* BaseMesh;
};