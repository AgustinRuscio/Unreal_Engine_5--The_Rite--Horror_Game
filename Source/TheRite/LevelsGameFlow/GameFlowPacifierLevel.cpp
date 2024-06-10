//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "GameFlowPacifierLevel.h"
#include "Engine/RectLight.h"
#include "TheRite/Interactuables/LightSwitch.h"
#include "Engine/TriggerVolume.h"
#include "TheRite/AmbientObjects/EmergencyLights.h"
#include "TheRite/Interactuables/Ladder.h"
#include "TheRite/Interactuables/Door.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Characters/Alex.h"

#include "BasePlayerSettingsSetter.h"
#include "TheRite/AmbientObjects/Candle.h"
#include "FetusPuzzle.h"

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
	
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
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
		Element->TurnOff();
	}

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_PowerRestored);
	Door_BedRoom->SetLockedState(false);
	Door_BedRoom->Open();
}

void AGameFlowPacifierLevel::EndGame()
{
	for (auto Element : Candles_EndGame)
	{
		Element->TurnOn();
	}
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_EndGame);
	Door_EndGame->SetLockedState(false);
}

void AGameFlowPacifierLevel::BindColliderMethods()
{
	TriggerVolume_LightsOut->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerLightsOutEventOverlap);
	TriggerVolume_EndGmaePass->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerEndGamePassOverlap);

	
	TriggerVolume_LucyRoom->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerLucyRoomOverlap);
	TriggerVolume_LucyRoom->OnActorEndOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerLucyRoomOverlapEnd);
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
	 	Element->TurnOn();
	 }

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(.15f, 3, true, true, true, true);
	
	TriggerVolume_LightsOut->Destroy();
}

void AGameFlowPacifierLevel::OnTriggerEndGamePassOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || bEndGamePassDone) return;
	bEndGamePassDone = true;
	
	Door_EndGame->HardClosing();
	
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(1, 5, true, true, true, true);
	
	TriggerVolume_EndGmaePass->Destroy();
}

void AGameFlowPacifierLevel::OnTriggerLucyRoomOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;
	
	PlayerSettingsSetter->SetUseLighter(false);
	Player->ForceLighterOff();
}

void AGameFlowPacifierLevel::OnTriggerLucyRoomOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;
	
	PlayerSettingsSetter->SetUseLighter(true);
}