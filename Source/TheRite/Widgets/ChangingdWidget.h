//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------



#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* ChangingText;

	UFUNCTION()
	virtual void SetKeyMode(bool isGamepad);

	void  SetChangingText(FText newText);
};