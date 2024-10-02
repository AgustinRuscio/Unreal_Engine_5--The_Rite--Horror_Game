//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "LevelsGameState.h"
#include "SaveData.h"
#include "Kismet/GameplayStatics.h"

#define PRINTING(X) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT(X)));

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
FSaveGameData ALevelsGameState::GetSaveData() const
{
	return GameData;
}

//----------------------------------------------------------------------------------------------------------------------
void ALevelsGameState::SaveData(float mouseSensitivity)
{
	USaveData* saveGameDataInstance = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass()));

	saveGameDataInstance->MouseSensitivity = mouseSensitivity;

	UGameplayStatics::SaveGameToSlot(saveGameDataInstance, TEXT("SavedGame"), 0);

	PRINTING("Saved");
}

//----------------------------------------------------------------------------------------------------------------------
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
		GetWorld()->GetTimerManager().SetTimer(WaitForInitializationTimerHandle,WaitForInitializationDelegate, 0.1f, false);
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