//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPauseOpen);

class AAlex;

UCLASS()
class THERITE_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(BlueprintAssignable)
	FOnPauseOpen OnPauseOpen;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void OnResume();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	AAlex* Player;
};