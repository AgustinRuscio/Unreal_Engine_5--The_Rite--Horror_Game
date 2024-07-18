//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheRite/Characters/Alex.h"
#include "GameFlowGameBegin.generated.h"

class ULevelSequence;

UCLASS()
class THERITE_API AGameFlowGameBegin : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameFlowGameBegin();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetNeededValues();
	
	void PlayBeginSequence();
	
	UFUNCTION()
	void BeginSequenceFinished();

private:
	UPROPERTY(EditAnywhere, Category= "Sequence")
	ULevelSequence* LS_BeginSequence;

	AAlex* Player;
};