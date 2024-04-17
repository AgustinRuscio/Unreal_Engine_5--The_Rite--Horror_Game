//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheRite/AmbientObjects/Candle.h"
#include "TheRite/Interactuables/Interactor.h"
#include "CandleGuideController.generated.h"

UCLASS()
class THERITE_API ACandleGuideController : public AActor
{
	GENERATED_BODY()
	
private:	
	UPROPERTY(EditAnywhere, Category= "Settings")
	AInteractor* MyInteractor;

	UFUNCTION()
	void GuideChange(AInteractor* interactor);

	UPROPERTY(EditAnywhere, Category= "States")
	TArray<ACandle*> PlaceGuideCandles;
	
	UPROPERTY(EditAnywhere, Category= "States")
	TArray<ACandle*> NextPlaceGuideCandles;
	
protected:
	virtual void BeginPlay() override;

public:	
	ACandleGuideController();
};