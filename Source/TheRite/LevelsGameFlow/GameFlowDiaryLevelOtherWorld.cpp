//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "GameFlowDiaryLevelOtherWorld.h"
#include "InOrdenSelectionPuzzleFlow.h"
#include "Components/LightComponent.h"
#include "Engine/SpotLight.h"
#include "TheRite/Interactuables/Door.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"

AGameFlowDiaryLevelOtherWorld::AGameFlowDiaryLevelOtherWorld()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AGameFlowDiaryLevelOtherWorld::BeginPlay()
{
	Super::BeginPlay();

	InitializeValues();
	BindTriggers();
	BindMethods();
}

void AGameFlowDiaryLevelOtherWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameFlowDiaryLevelOtherWorld::EndGame()
{
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_LastAudio);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_LightsOut);
	
	for (auto Element : InGameLights)
	{
		Element->TurnOff();
	}
	
	for (auto Element : Light_EndGame)
	{
		Element->GetLightComponent()->SetIntensity(20);
	}

	Doors_BathRoom->SetLockedState(true);
	Doors_BathRoom->HardClosing();
	
	Doors_BedRoom->SetLockedState(true);
	Doors_BedRoom->HardClosing();
	
	Doors_EndGame->SetLockedState(false);
	
	Player->ForceTurnLighterOn();
	Player->SetPlayerOptions(true, false, false);
}

void AGameFlowDiaryLevelOtherWorld::BindTriggers()
{
}

void AGameFlowDiaryLevelOtherWorld::BindMethods()
{
	
	InOrderPOuzzleController->OnPuzzleFinished.AddDynamic(this, &AGameFlowDiaryLevelOtherWorld::EndGame);
}

void AGameFlowDiaryLevelOtherWorld::InitializeValues()
{
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	for (auto Element : Light_EndGame)
	{
		Element->GetLightComponent()->SetIntensity(0);
	}
}

