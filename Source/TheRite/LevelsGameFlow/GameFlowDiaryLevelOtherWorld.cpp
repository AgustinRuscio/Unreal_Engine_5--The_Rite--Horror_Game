//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "GameFlowDiaryLevelOtherWorld.h"
#include "InOrdenSelectionPuzzleFlow.h"
#include "Components/LightComponent.h"
#include "Engine/SpotLight.h"
#include "Engine/RectLight.h"
#include "Engine/TriggerVolume.h"
#include "TheRite/Interactuables/Door.h"
#include "Animation/SkeletalMeshActor.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
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
	
	for (auto Element : Lights_AllLights)
	{
		Element->TurnOff();
	}
	
	for (auto Element : Lights_SpotLightEndGame)
	{
		Element->GetLightComponent()->SetIntensity(20);
	}
	
	for (auto Element : Lights_Altar)
	{
		Element->GetLightComponent()->SetIntensity(0);
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
	TriggerVolume_LivingRoomEvent->OnActorBeginOverlap.AddDynamic(this, &AGameFlowDiaryLevelOtherWorld::a);
}

void AGameFlowDiaryLevelOtherWorld::BindMethods()
{
	InOrderPOuzzleController->OnPuzzleFinished.AddDynamic(this, &AGameFlowDiaryLevelOtherWorld::EndGame);
}

void AGameFlowDiaryLevelOtherWorld::InitializeValues()
{
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	for (auto Element : Lights_SpotLightEndGame)
	{
		Element->GetLightComponent()->SetIntensity(0);
	}
}

void AGameFlowDiaryLevelOtherWorld::a(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;

	for (auto Element : Lights_LivingEvent)
	{
		Element->TurnOff();
	}

	for (auto Element : Lights_OtherLivingEvent)
	{
		Element->Destroy();
	}
	
	for (auto Element : Skeletals_Sofa)
	{
		Element->Destroy();
	}
	
	if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_LivingRoomEvent))
	{
		FTimerDelegate OnTimerCompleted;

		OnTimerCompleted.BindLambda([&]
		{
			for (auto Element : Lights_LivingEvent)
			{
				Element->TurnOn();
			}
		});
		GetWorld()->GetTimerManager().SetTimer(Timer_LivingRoomEvent, OnTimerCompleted, 1.5f, false);
	}
	
	TriggerVolume_LivingRoomEvent->Destroy();
}