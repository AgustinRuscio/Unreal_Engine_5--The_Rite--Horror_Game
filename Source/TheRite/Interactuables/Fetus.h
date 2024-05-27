//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Fetus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCorrectFetus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWrongFetus);

class UNiagaraComponent;

UCLASS()
class THERITE_API AFetus : public AInteractor
{
	GENERATED_BODY()
	
public:	
	AFetus();
	
//---------------- System Class Methods
	virtual void Interaction() override;

	void ResetFetus();
public:
	bool GetIsCorrectFetus();
	
	FOnCorrectFetus OnCorrectFetus;
	FOnWrongFetus OnWrongFetus;
	
private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bIsCorrectFetus;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float ParticleDuration;
	
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* FetusMesh;

	UPROPERTY(EditAnywhere, Category = "Niagara", meta=(AllowPrivateAccess = true))
	UNiagaraComponent* NiagaraSytem_Blood;
	
	FTimerHandle Timer_LightsOut;
};