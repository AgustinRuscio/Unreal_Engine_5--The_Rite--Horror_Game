//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheRite/Interactuables/Interactor.h"
#include "ChangingdWidget.generated.h"

class UTextBlock;
class UImage;



UCLASS()
class THERITE_API UChangingdWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void SetKeyMode(bool isGamepad);

	void  SetChangingText(FText newText);

	UFUNCTION(BlueprintImplementableEvent) 
	void OnInteraction(AInteractor* Interactable);
	
private:
	void SetGamepadImages();
	void SetKeyboardImages();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UImage*> DisplayImmages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* ChangingText;

protected:
	UPROPERTY(EditAnywhere)
	TArray<UTexture*> GamepadKeyImage;
	
	UPROPERTY(EditAnywhere)
	TArray<UTexture*> KeyboardKeyImage;

private:
	int8 Index = 0;
};