//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "LevelsGameState.h"
#include "SaveData.h"
#include "Kismet/GameplayStatics.h"

#define PRINTING(X) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT(X)));

FSaveGameData ALevelsGameState::GetSaveData() const
{
	return GameData;
}

void ALevelsGameState::BeginPlay()
{
	Super::BeginPlay();
	
	LoadData();
}

void ALevelsGameState::SaveData(float mouseSensitivity)
{
	USaveData* saveGameDataInstance = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass()));

	saveGameDataInstance->MouseSensitivity = mouseSensitivity;

	UGameplayStatics::SaveGameToSlot(saveGameDataInstance, TEXT("SavedGame"), 0);

	PRINTING("Saved");
}

void ALevelsGameState::LoadData()
{
	if(!UGameplayStatics::DoesSaveGameExist("SavedGame", 0)) return;
	
	USaveData* saveGameDataInstance = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass()));

	saveGameDataInstance = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot("SavedGame", 0));

	GameData.MouseSensitivity = saveGameDataInstance->MouseSensitivity;
	GameData.PuzzleResolveIndex = saveGameDataInstance->PuzzleResolveIndex;

	OnGameLoaded.Broadcast();
	
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("Load Mouse: %f"),GameData.MouseSensitivity ));
}