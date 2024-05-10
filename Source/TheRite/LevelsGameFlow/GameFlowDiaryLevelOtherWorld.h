
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFlowDiaryLevelOtherWorld.generated.h"

class AInOrdenSelectionPuzzleFlow;


UCLASS()
class THERITE_API AGameFlowDiaryLevelOtherWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameFlowDiaryLevelOtherWorld();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void EndGame();
public:	

private:

	UPROPERTY(EditAnywhere, Category= "Settings")
	AInOrdenSelectionPuzzleFlow* InOrderPOuzzleController;
};
