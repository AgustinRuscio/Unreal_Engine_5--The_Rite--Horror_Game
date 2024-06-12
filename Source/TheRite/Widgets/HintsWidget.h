//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HintsWidget.generated.h"

class UImage;

UCLASS()
class THERITE_API UHintsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void MakeVisible();

private:
	void JoystickChecker();
	void TimerChecker(float deltaTime);
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Widget Components")
	UImage* KeyImage;
	
private:
	bool bIsOn;
	bool bJoystick;

	UPROPERTY(EditAnywhere, Category= "States")
	float TimerCD = 7.0f;
	float Timer = 0.0f;
	
	UPROPERTY(EditAnywhere, Category= "Textures")
	UTexture2D* SquareTexture;
	
	UPROPERTY(EditAnywhere, Category= "Textures")
	UTexture2D* MTexture;
};