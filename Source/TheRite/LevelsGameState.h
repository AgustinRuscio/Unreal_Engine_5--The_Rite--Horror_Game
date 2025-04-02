//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LevelsGameState.generated.h"


struct FSaveGameData
{
	float MouseSensitivity;
	uint8 PuzzleResolveIndex;

	FSaveGameData()
	{
		MouseSensitivity = 1.f;
		PuzzleResolveIndex = 0;
	}
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameLoaded);

UCLASS()
class THERITE_API ALevelsGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FSaveGameData GetSaveData() const;

	FGameLoaded OnGameLoaded;
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	UFUNCTION(BlueprintCallable)
	void SaveData(float mouseSensitivity);

	UFUNCTION(BlueprintCallable)
	void LoadData();

private:

	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	FSaveGameData GameData;

	FTimerHandle WaitForInitializationTimerHandle;
	FTimerDelegate WaitForInitializationDelegate;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};