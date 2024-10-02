//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "PlayerStateTheRite.h"

#include "AlexPlayerController.h"
#include "LevelsGameState.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
void APlayerStateTheRite::SetMouseSensitivity(float NewSensitivity)
{
	MouseSensitivity = NewSensitivity;
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

	GameState = Cast<ALevelsGameState>(UGameplayStatics::GetGameState(GetWorld()));
	PlayerController = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	if(GameState)
		GameState->OnGameLoaded.AddDynamic(this, &APlayerStateTheRite::LoadValues);
}

//----------------------------------------------------------------------------------------------------------------------
void APlayerStateTheRite::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("Sensi : %f"), MouseSensitivity ));
}

//----------------------------------------------------------------------------------------------------------------------
void APlayerStateTheRite::LoadValues()
{
	auto saveData = GameState->GetSaveData();
	MouseSensitivity = saveData.MouseSensitivity;
}