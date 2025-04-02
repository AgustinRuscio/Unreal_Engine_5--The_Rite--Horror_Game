//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//CONTRUSCTOR
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Components")
	UImage* KeyImage;
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	UFUNCTION(BlueprintCallable)
	void MakeVisible();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bIsOn;
	bool bJoystick;

	UPROPERTY(EditAnywhere, Category= "States")
	float TimerCD = 7.0f;
	float Timer = 0.0f;
	
	UPROPERTY(EditAnywhere, Category= "Textures")
	UTexture2D* SquareTexture;
	
	UPROPERTY(EditAnywhere, Category= "Textures")
	UTexture2D* MTexture;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	void JoystickChecker();
	void TimerChecker(float deltaTime);
};