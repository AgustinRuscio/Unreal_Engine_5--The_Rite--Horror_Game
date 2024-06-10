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

public:
	ABasePlayerSettingsSetter();
	virtual void BeginPlay() override;

	void SetUseLighter(bool WillUseLighter);
	void SetCanRun(bool WillRun);
	
private:
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "Player Settings for running in begin play"))
	bool bWillRun;
	
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "Player Settings for use of lighter in begin play"))
	bool bWilUseLighter;
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "Player Settings for show the lighter use reminder begin play"))
	bool bWilShowLighterReminder;
	
	AAlex* Player;
};