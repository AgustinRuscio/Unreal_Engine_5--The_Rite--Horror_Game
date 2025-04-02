//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ABasePlayerSettingsSetter();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
//---------------- Setter Methods
	void SetUseLighter(bool WillUseLighter);
	void SetCanRun(bool WillRun);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "Player Settings for running in begin play"))
	bool bWillRun;
	
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "Player Settings for use of lighter in begin play"))
	bool bWilUseLighter;
	UPROPERTY(EditAnywhere, Category = "Settings", meta=(ToolTip = "Player Settings for show the lighter use reminder begin play"))
	bool bWilShowLighterReminder;
	
	AAlex* Player;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
};