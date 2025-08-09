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
	FString LastLevelName;

	FSaveGameData()
	{
		MouseSensitivity = 1.f;
		PuzzleResolveIndex = 0;
		LastLevelName = "";
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
	FGameLoaded OnGameLoaded;
	
	FString CurrentLevelName;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	UFUNCTION(BlueprintCallable)
	bool DoesSaveDataExiste() const;

	UFUNCTION(BlueprintCallable)
	bool IsLastLevelChargeable() const;

	bool IsThisLevelChargable() const;

	UFUNCTION(BlueprintCallable)
	FString GetLastLevelSaved();

	FSaveGameData GetSaveData() const;

	UFUNCTION(BlueprintCallable)
	void SaveData(float mouseSensitivity);

	UFUNCTION(BlueprintCallable)
	void LoadData();

	UFUNCTION(BlueprintCallable)
	void ResetLastLevelOpened();

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