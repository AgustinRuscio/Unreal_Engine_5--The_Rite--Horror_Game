//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "SecondCorridorFlow.h"
#include "LightsPuzzle.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/AmbientObjects/CustomLight.h"
#include "TheRite/AmbientObjects/AmbientSoundPlayer.h"
#include "Engine/TargetPoint.h"
#include "Math/UnrealMathUtility.h"
#include <TheRite/Characters/Alex.h>

//----------------------------------------------------------------------------------------------------------------------
ASecondCorridorFlow::ASecondCorridorFlow() : m_TimeToTeleport(2.f)
{
	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AAlex>(GetWorld()->GetFirstPlayerController()->GetPawn());

	LightsPuzzle->OnPuzzleComplete.AddDynamic(this, &ASecondCorridorFlow::OnLightsPuzzleCompleted);

	//------- Glass Col timeline
	FOnTimelineFloat MoveInteractorTimelineCallback;
	MoveInteractorTimelineCallback.BindUFunction(this, FName("FeedBackTick"));
	TimeLineFeedBack.AddInterpFloat(CurveFloatMoveLightsKeyInteractor, MoveInteractorTimelineCallback);

	FOnTimelineEventStatic MoveInteractorTimelineFinishedCallback;
	MoveInteractorTimelineFinishedCallback.BindUFunction(this, FName("FeedBackFinished"));
	TimeLineFeedBack.SetTimelineFinishedFunc(MoveInteractorTimelineFinishedCallback);
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHanldeTeleport);
	TimerDelegateTeleport.Unbind();
	TimeLineFeedBack.Stop();
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::Tick(float DeltaSeconds)
{
	TimeLineFeedBack.TickTimeline(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::OnLightsPuzzleCompleted()
{
	KeyLightsObject->SetCanInteract(false);

	OnLightsPuzzleCompletedFeedBack();
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::OnLightsPuzzleCompletedFeedBack()
{
	ToggleLights(false);
	ToggleSound(true);

	TimeLineFeedBack.PlayFromStart();

	if(GetWorld()->GetTimerManager().IsTimerActive(TimerHanldeTeleport)) return;

	TimerDelegateTeleport.BindLambda([this]()
		{
			TeleportPlayer();
		});

	GetWorld()->GetTimerManager().SetTimer(TimerHanldeTeleport, TimerDelegateTeleport, m_TimeToTeleport, false);
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::ToggleLights(bool LightsOn)
{
	for (auto light : FeedbackLights)
	{
		LightsOn ? light->TurnOn() : light->TurnOff();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::ToggleSound(bool Active)
{
	for (auto sound : FeedbackSounds)
	{
		Active ? sound->StartAudioManually(false, true) : sound->StopAudios();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::TeleportPlayer()
{
	if (!player) return;

	player->ForceLighterOff();
	player->ForceDisableInput();

	player->SetActorLocation(TeleportTargetPoint->GetActorLocation());
	player->SetActorRotation(TeleportTargetPoint->GetActorRotation());
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::FeedBackTick(float DeltaSeconds) { }

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::FeedBackFinished(float DeltaSeconds)
{
	ToggleLights(true);
	ToggleSound(false);

	if (!player) return;
	player->ForceEnableInput();
}