//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Fetus.generated.h"

class UNiagaraComponent;

UCLASS()
class THERITE_API AFetus : public AInteractor
{
	GENERATED_BODY()
	
public:	
	AFetus();
	
//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction() override;
	
private:

public:	

private:
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* FetusMesh;

	UPROPERTY(EditAnywhere, Category = "Niagara", meta=(AllowPrivateAccess = true))
	UNiagaraComponent* NiagaraSytem_Blood;
};