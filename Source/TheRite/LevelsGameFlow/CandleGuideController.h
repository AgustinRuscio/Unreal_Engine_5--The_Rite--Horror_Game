//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CandleGuideController.generated.h"

class ACandle;
class AInteractor;

UCLASS()
class THERITE_API ACandleGuideController : public AActor
{
	GENERATED_BODY()

public:	
	ACandleGuideController();
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void GuideChange(AInteractor* interactor);

	void TurnOffPrevCandles();
	void TurnOnNextCandles();
	
private:	
	UPROPERTY(EditAnywhere, Category= "Settings")
	AInteractor* MyInteractor;

	UPROPERTY(EditAnywhere, Category= "States")
	TArray<ACandle*> PlaceGuideCandles;
	
	UPROPERTY(EditAnywhere, Category= "States")
	TArray<ACandle*> NextPlaceGuideCandles;
};