//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "GameFlowPacifierLevel.h"
#include "Engine/RectLight.h"
#include "TheRite/Interactuables/LightSwitch.h"
#include "Engine/TriggerVolume.h"
#include "TheRite/Interactuables/Ladder.h"
#include "TheRite/Interactuables/Door.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Characters/Alex.h"

AGameFlowPacifierLevel::AGameFlowPacifierLevel()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameFlowPacifierLevel::BeginPlay()
{
	Super::BeginPlay();

	LightSwitch_TermicalSwitch->OnInteractionTrigger.AddDynamic(this, &AGameFlowPacifierLevel::OnLightsOnEvent);
	GameFlow_FetusPuzzle->OnPuzzleComplete.AddDynamic(this, &AGameFlowPacifierLevel::EndGame);
	AtticLader->DisableLadder();
	
	BindColliderMethods();
}

void AGameFlowPacifierLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameFlowPacifierLevel::OnLightsOnEvent(AInteractor* Interactor)
{
	for (auto Element : EmergencyLights)
	{
		Element->GetLightComponent()->SetIntensity(0);
	}
	
	Door_BedRoom->SetLockedState(false);
	Door_BedRoom->Open();
}

void AGameFlowPacifierLevel::EndGame()
{
	for (auto Element : Candles_EndGame)
	{
		Element->TurnOn();
	}
	
	Door_EndGame->SetLockedState(false);
}

void AGameFlowPacifierLevel::BindColliderMethods()
{
	TriggerVolume_LightsOut->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerLightsOutEventOverlap);
}

void AGameFlowPacifierLevel::OnTriggerLightsOutEventOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || bLightsOutEventDone) return;
	bLightsOutEventDone = true;

	AtticLader->EnableLadder();
	Door_BathRoomRoom->SetLockedState(false);
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_LightsOut);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_PowerDowns);
	
	for (auto Element : Lights_AllLights)
	{
		Element->TurnOff();
	}

	for (auto Element : EmergencyLights)
	{
		Element->GetLightComponent()->SetIntensity(EmergencyLightsIntensity);
	}

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(.15f, 3, true, true, true, true);
	
	TriggerVolume_LightsOut->Destroy();
}