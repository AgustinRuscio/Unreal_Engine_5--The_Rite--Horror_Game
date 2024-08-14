//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/Components/Fader.h"
#include "Fetus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCorrectFetus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWrongFetus);

class UNiagaraSystem;
class UArrowComponent;
class UFadeObjectComponent;
class UAudioComponent;

UCLASS()
class THERITE_API AFetus : public AInteractor, public IFader
{
	GENERATED_BODY()
	
public:
	AFetus();
	
	bool GetIsCorrectFetus() const;
	
	virtual void Interaction() override;
	
//---------------- Status Methods
	void ResetFetus();

	void StartAudioComponent();
	
private:
	void SetFaderValues();

	UFUNCTION()
	void OnFadeActivated();
	
	UFUNCTION()
	void OnFadeDeactivate();
	
public:
	FOnCorrectFetus OnCorrectFetus;
	FOnWrongFetus OnWrongFetus;
	
private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bIsLetterPuzzle = true;
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bIsCorrectFetus;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float ParticleDuration;

	FVector InitialPosition;
	
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FetusMesh;

	UPROPERTY(EditAnywhere, Category = "Niagara", meta=(AllowPrivateAccess = true))
	UNiagaraSystem* NiagaraSytem_Blood;

	UPROPERTY(EditAnywhere, Category = "Arrow", meta=(AllowPrivateAccess = true))
	UArrowComponent* BloodSpawnLoscation;

	UPROPERTY(EditAnywhere, Category = "SFX", meta=(AllowPrivateAccess = true))
	UAudioComponent* AudioComponent;
	
	FTimerHandle Timer_LightsOut;

	UPROPERTY(EditAnywhere, Category = "Component", meta=(AllowPrivateAccess = true))
	UFadeObjectComponent* FadeComponent;
};