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
	UFUNCTION(BlueprintImplementableEvent)
	void Interact(bool InteractionDisable, bool NoIntractable, bool LockedDoor, bool PlayerTalking, bool IsMainItem);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMainInteractionTexture();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetInteractionTexture();
	
private:
	void SetLockedDoorImage();
	void SetCantInteractTexture();
	void SetNoneInteractionTexture();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* NoneInteractionTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* InteractionTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* MainInteractionTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* CantInteractTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* LockedDoorTexture;
};