
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
	
	friend FArchive& operator<<(FArchive& Ar, FSaveGameData& Data)
	{
		Ar << Data.MouseSensitivity;
		Ar << Data.PuzzleResolveIndex;
		return Ar;
	}
};

UCLASS()
class THERITE_API ALevelsGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	FSaveGameData GameData;
	
public:
	UFUNCTION(BlueprintCallable)
	void SaveData(float mouseSensitivity);

	UFUNCTION(BlueprintCallable)
	void LoadData();

	FSaveGameData GetSaveData() const;
};