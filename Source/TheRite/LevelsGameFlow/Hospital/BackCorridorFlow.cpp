//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "BackCorridorFlow.h"

#include "LeverPuzzle.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Triggers/TeleportPlayer.h"

//----------------------------------------------------------------------------------------------------------------------
ABackCorridorFlow::ABackCorridorFlow() : TimeToMovePlayerOnEndPuzzle(5.f)
{
	PrimaryActorTick.bCanEverTick = true;

}

//----------------------------------------------------------------------------------------------------------------------
void ABackCorridorFlow::ActivateZone() const
{
	for (auto Element : InitialDoors)
	{
		Element->SetLockedState(false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ABackCorridorFlow::BeginPlay()
{
	Super::BeginPlay();

	InitialTeleportPlayer->OnTeleportComplete.AddDynamic(this, &ABackCorridorFlow::OnPuzzleStarted);

	LeverPuzzle->OnPuzzleCompleted.AddDynamic(this, &ABackCorridorFlow::OnPuzzleEnd);
	PLayer = Cast<AAlex>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

}

//----------------------------------------------------------------------------------------------------------------------
void ABackCorridorFlow::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_PuzzleEnd);
	}

	TimerDelegate_PuzzleEnd.Unbind();
}

//----------------------------------------------------------------------------------------------------------------------
void ABackCorridorFlow::OnPuzzleStarted()
{
	for (auto Element : ActorsToDestroyOnPuzzleBegin)
	{
		Element->Destroy();
	}

	for (auto Element : EndDoors)
	{
		Element->SetLockedState(false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ABackCorridorFlow::OnPuzzleEnd()
{
	if(!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_PuzzleEnd))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SFX_PuzzleEnd_LightsOff);
		for (auto Element : AllLights)
		{
			Element->TurnOff();
		}

		EndPuzzleDoor->SetLockedState(false);
		PLayer->SetCanUseLighterState(false);
		PLayer->ForceLighterOff();
		UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake_Puzzle,UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(),0,1000);
		UGameplayStatics::PlaySound2D(GetWorld(), SFX_PuzzleEnd);

		TimerDelegate_PuzzleEnd.BindLambda([&]
		{
			PLayer->SetActorLocation(TargetPoint_EndPuzzle->GetActorLocation());
			PLayer->SetCanUseLighterState(true);
		});

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_PuzzleEnd, TimerDelegate_PuzzleEnd,TimeToMovePlayerOnEndPuzzle, false);
	}
}