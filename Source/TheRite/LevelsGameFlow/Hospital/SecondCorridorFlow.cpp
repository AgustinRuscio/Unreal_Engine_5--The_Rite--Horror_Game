//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "SecondCorridorFlow.h"

#include "Engine/TargetPoint.h"
#include "Math/UnrealMathUtility.h"

#include "TheRite/AmbientObjects/AmbientSoundPlayer.h"
#include "TheRite/AmbientObjects/CustomLight.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/Interactor.h"
#include "LightsPuzzle.h"
#include <Kismet/GameplayStatics.h>

//----------------------------------------------------------------------------------------------------------------------
ASecondCorridorFlow::ASecondCorridorFlow() : m_TimeToTeleport(2.f), m_FeedBackOffSetTime(2.f)
{
	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AAlex>(GetWorld()->GetFirstPlayerController()->GetPawn());
	EmblemObject->Dissapear();

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

	GetWorld()->GetTimerManager().ClearTimer(TimerHanldeFeedBackTimeOffset);
	TimerDelegateFeedBackTimeOffset.Unbind();

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
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHanldeFeedBackTimeOffset)) return;

	player->ForceLighterOff();
	player->ForceDisableInput();

	ToggleLights(false);
	ToggleSound(true);

	TimerDelegateFeedBackTimeOffset.BindLambda([this]()
		{

			TimeLineFeedBack.PlayFromStart();

			if (GetWorld()->GetTimerManager().IsTimerActive(TimerHanldeTeleport)) return;

			TimerDelegateTeleport.BindLambda([this]()
				{
					TeleportPlayer();

					UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake_Puzzle, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(), 0, 1000);

					EmblemObject->Appear();
					EmblemDoor->SetLockedState(false);
				});

			GetWorld()->GetTimerManager().SetTimer(TimerHanldeTeleport, TimerDelegateTeleport, m_TimeToTeleport, false);
		});

	GetWorld()->GetTimerManager().SetTimer(TimerHanldeFeedBackTimeOffset, TimerDelegateFeedBackTimeOffset, m_FeedBackOffSetTime, false);
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