#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "HintsWidget.generated.h"


UCLASS()
class THERITE_API UHintsWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category= "Textures")
	UTexture2D* SquareTexture;
	
	UPROPERTY(EditAnywhere, Category= "Textures")
	UTexture2D* MTexture;

	bool bIsOn;
	bool bJoystick;

	float Timer = 0.0f;
	
	UPROPERTY(EditAnywhere, Category= "States")
	float TimerCD = 7.0f;
	
private:
	void JoystickChecker();
	void TimerChecker(float deltaTime);
	
public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Widget Components")
	UImage* KeyImage;

	UFUNCTION(BlueprintCallable)
	void MakeVisible();
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};