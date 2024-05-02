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
	UFUNCTION(BlueprintCallable)
	void Interact(bool Visible, bool LockedDoor, bool Wait, bool MainItem);

private:
	void SetLockedDoorImage();
	void SetWaitImage();
	void SetVisibleImage();
	void SetMainObjectImage();
	void SetDefaultImage();
	
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
};