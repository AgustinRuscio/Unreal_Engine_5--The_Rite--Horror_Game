//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlayerSettingsSetter.generated.h"


class AAlex;

UCLASS()
class THERITE_API ABasePlayerSettingsSetter : public AActor
{
	GENERATED_BODY()
	
private:
	AAlex* Player;

	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "Player Settings for running in begin play"))
	bool bWillRun;
	
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "Player Settings for use of lighter in begin play"))
	bool bWilUseLighter;
	
protected:
	virtual void BeginPlay() override;

public:	
	ABasePlayerSettingsSetter();
};