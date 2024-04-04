//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class AAlex;
UCLASS()
class THERITE_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	AAlex* Player;
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void OnResume();
};