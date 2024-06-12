//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyWidget.generated.h"

class UTextBlock;

UCLASS()
class THERITE_API UKeyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetKeyZoneText(FString newZone);
	
public:
	UPROPERTY(BlueprintReadWrite)
	FString ZoneText;
	UPROPERTY(EditAnywhere)
	FString NotChangableText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* TextComponent;
};