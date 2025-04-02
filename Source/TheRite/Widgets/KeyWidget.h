//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyWidget.generated.h"

class UTextBlock;

UCLASS()
class THERITE_API UKeyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(BlueprintReadWrite)
	FString ZoneText;
	UPROPERTY(EditAnywhere)
	FString NotChangableText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* TextComponent;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	UFUNCTION(BlueprintCallable)
	void SetKeyZoneText(FString newZone);
};