//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "LevelsGameState.h"
#include "SaveData.h"
#include "Kismet/GameplayStatics.h"

#define PRINTING(X) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT(X)));

const FString SAVED_SLOT = TEXT("SavedGame");

//*****************************Public*********************************************
//********************************************************************************


//----------------------------------------------------------------------------------------------------------------------
bool ALevelsGameState::DoesSaveDataExiste() const
{
	return UGameplayStatics::DoesSaveGameExist(SAVED_SLOT, 0);
}

bool ALevelsGameState::IsLastLevelChargeable() const
{
	if (!UGameplayStatics::DoesSaveGameExist(SAVED_SLOT, 0)) return false;

	USaveData* saveGameDataInstance = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(SAVED_SLOT, 0));

	if (saveGameDataInstance == nullptr) return false;

	return saveGameDataInstance->LastLevelName != "MainMenu" && saveGameDataInstance->LastLevelName != "Credits" && saveGameDataInstance->LastLevelName != "RealWorld_Begin" && saveGameDataInstance->LastLevelName != "";
}

//----------------------------------------------------------------------------------------------------------------------
bool ALevelsGameState::IsThisLevelChargable() const
{
	auto current =  UGameplayStatics::GetCurrentLevelName(GetWorld());

	return current != "MainMenu" && current != "Credits" && current != "RealWorld_Begin" && current != "";
}

//----------------------------------------------------------------------------------------------------------------------
FString ALevelsGameState::GetLastLevelSaved()
{
	if (!UGameplayStatics::DoesSaveGameExist(SAVED_SLOT, 0)) return "false";

	USaveData*  saveGameDataInstance = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(SAVED_SLOT, 0));

	if (saveGameDataInstance == nullptr) return "false";

	return saveGameDataInstance->LastLevelName;
}

//----------------------------------------------------------------------------------------------------------------------
FSaveGameData ALevelsGameState::GetSaveData() const
{
	return GameData;
}

//----------------------------------------------------------------------------------------------------------------------
void ALevelsGameState::SaveData(float mouseSensitivity)
{
	USaveData* saveGameDataInstance = nullptr;
	
	if (!UGameplayStatics::DoesSaveGameExist(SAVED_SLOT, 0))
	{
		saveGameDataInstance = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass()));
	}
	else
	{
		saveGameDataInstance = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(SAVED_SLOT, 0));
	}

	saveGameDataInstance->MouseSensitivity = mouseSensitivity;

	UGameplayStatics::SaveGameToSlot(saveGameDataInstance, SAVED_SLOT, 0);

	PRINTING("Saved");
}

//----------------------------------------------------------------------------------------------------------------------
void ALevelsGameState::LoadData()
{
	USaveData* saveGameDataInstance = nullptr;

	if(!UGameplayStatics::DoesSaveGameExist(SAVED_SLOT, 0))
	{
		CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
		
		saveGameDataInstance = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass()));

		if (saveGameDataInstance->LastLevelName.IsEmpty())
		{
			saveGameDataInstance->LastLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
		}

		GameData.LastLevelName = saveGameDataInstance->LastLevelName;

		UGameplayStatics::SaveGameToSlot(saveGameDataInstance, SAVED_SLOT, 0);	
	}
	else
	{
		saveGameDataInstance = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(SAVED_SLOT, 0));

		GameData.MouseSensitivity = saveGameDataInstance->MouseSensitivity;
		GameData.PuzzleResolveIndex = saveGameDataInstance->PuzzleResolveIndex;

		CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

		if(IsLastLevelChargeable())
		{
			if (IsThisLevelChargable())
			{
				saveGameDataInstance->LastLevelName = CurrentLevelName;
			}
		}
		else
		{
			saveGameDataInstance->LastLevelName = CurrentLevelName;
		}
		
		GameData.LastLevelName = saveGameDataInstance->LastLevelName;

		UGameplayStatics::SaveGameToSlot(saveGameDataInstance, SAVED_SLOT, 0);	
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Last level: %s"), *GameData.LastLevelName));

	OnGameLoaded.Broadcast();

	//GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("Load Mouse: %f"),GameData.MouseSensitivity ));
}

//----------------------------------------------------------------------------------------------------------------------
void ALevelsGameState::ResetLastLevelOpened()
{
	if (!UGameplayStatics::DoesSaveGameExist(SAVED_SLOT, 0)) return;

	USaveData* saveGameDataInstance = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(SAVED_SLOT, 0));

	if (saveGameDataInstance == nullptr) return;

	saveGameDataInstance->LastLevelName = "";

	UGameplayStatics::SaveGameToSlot(saveGameDataInstance, SAVED_SLOT, 0);
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ALevelsGameState::BeginPlay()
{
	Super::BeginPlay();

	WaitForInitializationDelegate.BindLambda([&]
	{
		LoadData();
	});
	
	if(!GetWorld()->GetTimerManager().IsTimerActive(WaitForInitializationTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(WaitForInitializationTimerHandle,WaitForInitializationDelegate, 0.2f, false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALevelsGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(WaitForInitializationTimerHandle);
	}

	if(WaitForInitializationDelegate.IsBound())
	{
		WaitForInitializationDelegate.Unbind();
	}
}