#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "KeyWidget.generated.h"


UCLASS()
class THERITE_API UKeyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString ZoneText;
	UPROPERTY(EditAnywhere)
	FString NotChangableText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* TextComponent;
	
	UFUNCTION(BlueprintCallable)
	void SetKeyZoneText(FString newZone);
};