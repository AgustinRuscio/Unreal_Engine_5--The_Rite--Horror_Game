//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "LittleBedroomFlow.h"
#include "Engine/TargetPoint.h"
#include "TheRite/AmbientObjects/CustomLight.h"
#include "TheRite/AmbientObjects/AmbientSoundPlayer.h"
#include "TheRite/AmbientObjects/Candle.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Engine/TriggerVolume.h"
#include <Kismet/GameplayStatics.h>

//----------------------------------------------------------------------------------------------------------------------
ALittleBedroomFlow::ALittleBedroomFlow() : bDoOnce(false), m_TimeToTeleport(2.f), m_TimeToDestroy(1.f)
{
	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ALittleBedroomFlow::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AAlex>(GetWorld()->GetFirstPlayerController()->GetPawn());

	TeleportInteractor->OnInteractionTrigger.AddDynamic(this, &ALittleBedroomFlow::OnTeleportBegin);
	TriggerBox->OnActorBeginOverlap.AddDynamic(this, &ALittleBedroomFlow::BeginOverlap);
}

//----------------------------------------------------------------------------------------------------------------------
void ALittleBedroomFlow::OnTeleportBegin(AInteractor* interactor)
{
	PerfromFeedBack();

	if(GetWorld()->GetTimerManager().IsTimerActive(TimerHanldeTeleport)) return;

	Player->ForceDisableInput();
	Player->ForceLighterOff();

	TimerDelegateTeleport.BindLambda([this]
		{
			TeleportPlayer();
		});

	GetWorld()->GetTimerManager().SetTimer(TimerHanldeTeleport, TimerDelegateTeleport, m_TimeToTeleport, false);
}

//----------------------------------------------------------------------------------------------------------------------
void ALittleBedroomFlow::TeleportPlayer()
{
	if (!Player) return;

	StopFeedBack();

	Player->ForceEnableInput();

	Player->SetActorLocation(TeleportTargetPoint->GetActorLocation());
	Player->SetActorRotation(TeleportTargetPoint->GetActorRotation());
}

//----------------------------------------------------------------------------------------------------------------------
void ALittleBedroomFlow::PerfromFeedBack()
{
	LightToggle(false);

	for (auto current : FeedbackSounds)
	{
		current->StartAudioManually(true, true);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALittleBedroomFlow::StopFeedBack()
{
	for (auto current : FeedbackSounds)
	{
		current->StopAudios();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALittleBedroomFlow::DestroyTiffany()
{
	if (bDoOnce) return;
	bDoOnce = true;

	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHanldeDestroyTiffany)) return;

	for (auto current : FeedbackSoundsDestroyTiffany)
	{
		UGameplayStatics::SpawnSound2D(GetWorld(), current);
	}

	Player->ForceLighterOff();
	Player->SetCanUseLighterState(false);

	LightToggle(false);

	for (auto current : ActorsToDestroy)
	{
		current->Destroy();
	}

	TimerDelegateDestroyTiffany.BindLambda([this]
		{
			LightToggle(true);

			Player->SetCanUseLighterState(true);
		});

	GetWorld()->GetTimerManager().SetTimer(TimerHanldeDestroyTiffany, TimerDelegateDestroyTiffany, m_TimeToDestroy, false);

}

//----------------------------------------------------------------------------------------------------------------------
void ALittleBedroomFlow::LightToggle(bool active)
{
	for (auto current : FeedbackLights)
	{
		active ? current->TurnOn() : current->TurnOff();
	}

	for (auto current : FeedbackCandles)
	{
		active ? current->TurnOn() : current->TurnOff();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALittleBedroomFlow::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == Player)
	{
		DestroyTiffany();
	}
}