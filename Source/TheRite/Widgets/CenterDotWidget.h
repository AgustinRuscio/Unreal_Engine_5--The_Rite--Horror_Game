//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CenterDotWidget.generated.h"

class UImage;

UCLASS()
class THERITE_API UCenterDotWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* CompleteCircle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* InteractCircle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* MainInteractCircle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* Talking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* ClosedDoor;
	
	UFUNCTION(BlueprintCallable)
	void Interact(bool Visible, bool LockedDoor, bool Wait, bool MainItem);
};