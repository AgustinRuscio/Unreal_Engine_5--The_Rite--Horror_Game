//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "TheRite/Interactuables/SimpleFocusableObject.h"
#include "GameFramework/Actor.h"
#include "LightsPortrait.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPortraitColorChange);

UCLASS()
class THERITE_API ALightsPortrait : public ASimpleFocusableObject
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ALightsPortrait();

	UPROPERTY(EditAnywhere, Category = "Settings")
	class USpotLightComponent* Light;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TArray<FLinearColor> SwitcheableColors;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FLinearColor CorrectColor;

	int8 ColorIndex = -1;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnPortraitColorChange OnLightChange;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	bool GetCurrentCorrectState() const;

	virtual void Interaction() override;

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	class UDualButtonWidget* Widget;

	UPROPERTY(EditAnywhere, Category = "FeedBack")
	USoundBase* SFX_Switch;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnYesButtonPressed();

	UFUNCTION()
	void OnNoButtonPressed();
};