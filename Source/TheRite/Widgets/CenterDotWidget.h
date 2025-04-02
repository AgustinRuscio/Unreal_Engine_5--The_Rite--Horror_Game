//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CenterDotWidget.generated.h"

class UImage;

UCLASS()
class THERITE_API UCenterDotWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
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

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	UFUNCTION(BlueprintImplementableEvent)
	void Interact(bool InteractionDisable, bool NoIntractable, bool LockedDoor, bool PlayerTalking, bool IsMainItem);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMainInteractionTexture();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetInteractionTexture();
	
private:
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	void SetLockedDoorImage();
	void SetCantInteractTexture();
	void SetNoneInteractionTexture();
};