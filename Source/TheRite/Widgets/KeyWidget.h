#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyWidget.generated.h"


UCLASS()
class THERITE_API UKeyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString ZoneText;

	UFUNCTION(BlueprintCallable)
	void SetKeyZoneText(FText newZone);
};