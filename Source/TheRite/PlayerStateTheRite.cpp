//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "PlayerStateTheRite.h"
#include "LevelsGameState.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
void APlayerStateTheRite::SetMouseSensitivity(float NewSensitivity)
{
	MouseSensitivity = NewSensitivity;
	OnPlayerValuesLoaded.Broadcast(this);
}

//----------------------------------------------------------------------------------------------------------------------
float APlayerStateTheRite::GetMouseSensitivity() const
{
	return MouseSensitivity;
}

//----------------------------------------------------------------------------------------------------------------------
void APlayerStateTheRite::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<ALevelsGameState>(GetWorld()->GetGameState());
	
	if(GameState)
		GameState->OnGameLoaded.AddDynamic(this, &APlayerStateTheRite::LoadValues);
}

//----------------------------------------------------------------------------------------------------------------------
void APlayerStateTheRite::LoadValues()
{
	if (GameState == nullptr) return;

	auto saveData = GameState->GetSaveData();
	MouseSensitivity = saveData.MouseSensitivity;

	OnPlayerValuesLoaded.Broadcast(this);
}