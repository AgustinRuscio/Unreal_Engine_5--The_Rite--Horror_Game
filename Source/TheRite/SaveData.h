//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveData.generated.h"

UCLASS()
class THERITE_API USaveData : public USaveGame
{
	GENERATED_BODY()

	USaveData();

public:
	UPROPERTY(EditAnywhere)
	float MouseSensitivity;
	
	UPROPERTY(EditAnywhere)
	uint8 PuzzleResolveIndex;
};