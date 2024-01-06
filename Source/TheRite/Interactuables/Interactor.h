#pragma once

#include "CoreMinimal.h"
#include "IInteractuable.h"
#include "GameFramework/Actor.h"
#include "Interactor.generated.h"

UCLASS()
class THERITE_API AInteractor : public AActor, public IIInteractuable
{
	GENERATED_BODY()
	
private:	

protected:
	UPROPERTY(EditAnywhere, Category="State")
	USoundBase* AudioToPlay;

	UPROPERTY(EditAnywhere, Category="State")
	bool bCanInteract;
	
	UPROPERTY(EditAnywhere, Category="State")
	bool bWillSound;

public:
	AInteractor();
	
	UFUNCTION()
	virtual void Interaction() override;
	UFUNCTION()
	virtual USoundBase* GetSound() override;
};