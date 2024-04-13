#include "LevelsGameState.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/MemoryReader.h"
#include "Misc/FileHelper.h"
#define PRINT(x) UE_LOG(LogTemp, Warning, TEXT(x));



void ALevelsGameState::BeginPlay()
{
	Super::BeginPlay();
	
	LoadData();
}



void ALevelsGameState::SaveData(float mouseSensitivity)
{
	FSaveGameData SaveData;
	SaveData.MouseSensitivity = mouseSensitivity;
	SaveData.PuzzleResolveIndex = 0;
	
	FBufferArchive Buffer;
	Buffer << SaveData;

	FString SavePath = FPaths::ProjectSavedDir() + TEXT("SaveGame.sav");
	FFileHelper::SaveArrayToFile(Buffer, *SavePath);
}

void ALevelsGameState::LoadData()
{
	PRINT("Load")
	FString LoadPath = FPaths::ProjectSavedDir() + TEXT("SaveGame.sav");
	TArray<uint8> LoadedData;

	if (FFileHelper::LoadFileToArray(LoadedData, *LoadPath))
	{
		FMemoryReader MemoryReader(LoadedData, true);

		FSaveGameData LoadedSaveData;
		MemoryReader << LoadedSaveData;

		GameData.MouseSensitivity = LoadedSaveData.MouseSensitivity;
		GameData.PuzzleResolveIndex = LoadedSaveData.PuzzleResolveIndex;

	}
}

FSaveGameData ALevelsGameState::GetSaveData() const
{
	return GameData;
}
