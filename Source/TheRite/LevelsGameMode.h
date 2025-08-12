//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelsGameMode.generated.h"

UCLASS()
class THERITE_API ALevelsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	UFUNCTION(BlueprintImplementableEvent)
	void UnlockAchievemetns(FName unlockName);



private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	int switchesInteractedPerLevel;

	TArray<class ALightSwitch*> AllLevelLightSwitcher;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnLightSwitchInteracted(class AInteractor* lightSwitch);
};