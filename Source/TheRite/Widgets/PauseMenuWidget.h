//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void OnResume();

public:
	UPROPERTY(BlueprintAssignable)
	FOnPauseOpen OnPauseOpen;
	
private:
	AAlex* Player;
};