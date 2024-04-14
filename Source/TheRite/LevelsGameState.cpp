//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "LevelsGameState.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/MemoryReader.h"
#include "SaveData.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/FileHelper.h"
#define PRINT(x) UE_LOG(LogTemp, Warning, TEXT(x));



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
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("Saved")));

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

FSaveGameData ALevelsGameState::GetSaveData() const
{
	return GameData;
}