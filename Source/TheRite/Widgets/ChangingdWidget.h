//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------



#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChangingdWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class THERITE_API UChangingdWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	BYTE Index = 0;
	void SetGamepadImages();
	void SetKeyboardImages();
	
protected:
	UPROPERTY(EditAnywhere)
	TArray<UTexture*> GamepadKeyImage;
	
	UPROPERTY(EditAnywhere)
	TArray<UTexture*> KeyboardKeyImage;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UImage*> DisplayImmages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* ChangingText;

	UFUNCTION()
	virtual void SetKeyMode(bool isGamepad);

	void  SetChangingText(FText newText);

	
};