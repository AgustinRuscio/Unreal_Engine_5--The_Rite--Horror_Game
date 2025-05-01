//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "LittleBedroomFlow.h"
#include "Engine/TargetPoint.h"
#include "TheRite/AmbientObjects/CustomLight.h"
#include "TheRite/AmbientObjects/AmbientSoundPlayer.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Interactor.h"

//----------------------------------------------------------------------------------------------------------------------
ALittleBedroomFlow::ALittleBedroomFlow() : m_TimeToTeleport(2.f)
{
	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ALittleBedroomFlow::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AAlex>(GetWorld()->GetFirstPlayerController()->GetPawn());

	TeleportInteractor->OnInteractionTrigger.AddDynamic(this, &ALittleBedroomFlow::OnTeleportBegin);
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
	for (auto current : FeedbackLights)
	{
		current->TurnOff();
	}

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