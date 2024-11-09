//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "BackCorridorFlow.h"

#include "LeverPuzzle.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Triggers/TeleportPlayer.h"

//----------------------------------------------------------------------------------------------------------------------
ABackCorridorFlow::ABackCorridorFlow()
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
	PLayer->SetActorLocation(TargetPoint_EndPuzzle->GetActorLocation());
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake_Puzzle,UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(),0,1000);
}