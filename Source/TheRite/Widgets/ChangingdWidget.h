
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "ChangingdWidget.generated.h"

UCLASS()
class THERITE_API UChangingdWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UTexture* GamepadKeyImage;
	
	UPROPERTY(EditAnywhere)
	UTexture* KeyboardKeyImage;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* DisplayImmage;

	UFUNCTION()
	virtual void SetKeyMode(bool isGamepad);
};
