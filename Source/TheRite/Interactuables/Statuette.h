#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Pawn.h"
#include "Statuette.generated.h"

UCLASS()
class THERITE_API AStatuette : public AInteractor
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;

public:	
	AStatuette();

	virtual void Interaction() override;

};
