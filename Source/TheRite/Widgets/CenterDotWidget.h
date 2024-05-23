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
	void Interact(bool InteractionDisable, bool LockedDoor, bool PlayerTalking, bool IsMainItem);

private:
	void SetLockedDoorImage();
	void SetCantInteractTexture();
	void SetNoneInteractionTexture();
	void SetMainInteractionTexture();
	void SetInteractionTexture();
	
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