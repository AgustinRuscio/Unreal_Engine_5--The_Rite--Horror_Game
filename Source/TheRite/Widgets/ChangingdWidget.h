//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheRite/Interactuables/Interactor.h"
#include "CommonActivatableWidget.h"
#include "ChangingdWidget.generated.h"

class UTextBlock;
class UImage;



UCLASS()
class THERITE_API UChangingdWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void SetKeyMode(bool isGamepad);

	void  SetChangingText(FText newText);

	UFUNCTION(BlueprintImplementableEvent) 
	void OnInteraction(AInteractor* Interactable);
	
	void SelfRemove();

private:
	
	void NativeOnActivated() override;

	void SetGamepadImages();
	void SetKeyboardImages();

	UFUNCTION()
	void AutoHide();
	
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
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	bool bAutoDisable;

	int8 Index = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float DeactivateTime;

	FTimerHandle Timer_ClockClue;
};