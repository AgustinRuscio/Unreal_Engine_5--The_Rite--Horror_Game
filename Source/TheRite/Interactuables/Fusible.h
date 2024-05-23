//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Fusible.generated.h"

class AFuseBox;

UCLASS()
class THERITE_API AFusible : public AInteractor
{
	GENERATED_BODY()
	
public:	
	AFusible();
	
//---------------- System Class Methods
	virtual void Interaction() override;

private:
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* FusibleMesh;

	UPROPERTY(EditAnywhere, Category = "Settings", meta=(AllowPrivateAccess = true))
	AFuseBox* FuseBox;
};