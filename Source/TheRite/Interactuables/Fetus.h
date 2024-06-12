//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Fetus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCorrectFetus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWrongFetus);

class UNiagaraSystem;

UCLASS()
class THERITE_API AFetus : public AInteractor
{
	GENERATED_BODY()
	
public:	
	AFetus();
	
	bool GetIsCorrectFetus();
	
//---------------- System Class Methods
	virtual void Interaction() override;

	void ResetFetus();
	
public:
	FOnCorrectFetus OnCorrectFetus;
	FOnWrongFetus OnWrongFetus;
	
private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bIsCorrectFetus;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float ParticleDuration;

	FVector InitialPosition;
	
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* FetusMesh;

	UPROPERTY(EditAnywhere, Category = "Niagara", meta=(AllowPrivateAccess = true))
	UNiagaraSystem* NiagaraSytem_Blood;

	UPROPERTY(EditAnywhere, Category = "Arrow", meta=(AllowPrivateAccess = true))
	UArrowComponent* BloodSpawnLoscation;
	
	FTimerHandle Timer_LightsOut;
};