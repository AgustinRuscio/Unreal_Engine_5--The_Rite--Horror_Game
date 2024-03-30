#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "SpectralObstacle.generated.h"

UCLASS()
class THERITE_API ASpectralObstacle : public AInteractor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Construction")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, Category = "Construction")
	UNiagaraComponent* NiagaraSystem;

	UPROPERTY(EditAnywhere, Category = "Construction")
	USoundBase* SpectralSound;
public:	
	ASpectralObstacle();

	UFUNCTION()
	void OnDestroy();
};