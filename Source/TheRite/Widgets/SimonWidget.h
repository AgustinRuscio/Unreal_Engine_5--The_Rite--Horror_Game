//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SimonWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSimonCompleted);

UCLASS()
class THERITE_API USimonWidget : public UUserWidget
{
	GENERATED_BODY()

public:   
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(BlueprintCallable)
	FOnSimonCompleted OnSimonCompleted;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	UFUNCTION()
	void SetWidgetParentLocation(const FVector& Location);

protected:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	
	UPROPERTY(BlueprintReadOnly)
	FVector ParentLocation;
};