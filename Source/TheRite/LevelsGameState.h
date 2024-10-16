//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
	FSaveGameData GetSaveData() const;
	
	UFUNCTION(BlueprintCallable)
	void SaveData(float mouseSensitivity);

	UFUNCTION(BlueprintCallable)
	void LoadData();

private:
	virtual void BeginPlay() override;
	
public:
	FGameLoaded OnGameLoaded;
	
private:
	FSaveGameData GameData;
};