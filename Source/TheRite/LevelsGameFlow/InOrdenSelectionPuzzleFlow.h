#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InOrdenSelectionPuzzleFlow.generated.h"

UCLASS()
class THERITE_API AInOrdenSelectionPuzzleFlow : public AActor
{
	GENERATED_BODY()
	
private:
	

protected:
	virtual void BeginPlay() override;

public:	
	AInOrdenSelectionPuzzleFlow();
	virtual void Tick(float DeltaTime) override;

};