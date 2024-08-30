//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "HideAndSeekPuzzle.h"

#include "ProsProcessModifier.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Characters/Alex.h"
#include "Engine/TargetPoint.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Interactuables/Interactor.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AHideAndSeekPuzzle::AHideAndSeekPuzzle()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
bool AHideAndSeekPuzzle::IsActive() const
{
	return bActive;
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AHideAndSeekPuzzle::BeginPlay()
{
	if(!bActive) return;
	
	Super::BeginPlay();

	InitializeValues();
}

//----------------------------------------------------------------------------------------------------------------------
void AHideAndSeekPuzzle::InitializeValues()
{
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Interactables_MainInteractable->SetActorLocation(TargetPoints_InitialLocations->GetActorLocation());
	Interactables_MainInteractable->SetActorRotation(TargetPoints_InitialLocations->GetActorRotation());

	Interactables_MainInteractable->SetAudioToPlay(SFX_AlexTalk[LocationIndex]);
	Interactables_MainInteractable->OnInteractionTrigger.AddDynamic(this, &AHideAndSeekPuzzle::OnNextPuzzleStep);
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Puzzle Steps Methods
void AHideAndSeekPuzzle::OnNextPuzzleStep(AInteractor* Interactable)
{
	if(!bFirstInteractionDone)
	{
		bFirstInteractionDone = true;
		OnPuzzleStarted.Broadcast();
		PostProcesModifierClass->ModifyPostProcessValues(PostProcessModiferValue, 1);
		UGameplayStatics::PlaySound2D(GetWorld(), SFX_ClockTicking, 1.5f, 0.5f);
		UGameplayStatics::PlaySound2D(GetWorld(), SFX_EventBegin, 1.5f);
	}
	else
	{
		PostProcesModifierClass->ModifyPostProcessValues(PostProcessModiferValue, 0.5f);
	}
	
	PlayerLighterStateSetter(false);
	
	LightsOff();
	
	InteractionFeedBack();
	
	LocationIndex == RelocationsQuantity ? PuzzleCompleted() : ReLocateInteractable();
}

//----------------------------------------------------------------------------------------------------------------------
void AHideAndSeekPuzzle::ReLocateInteractable()
{
	Interactables_MainInteractable->SetActorLocation(TargetPoints_MainLocations[LocationIndex]->GetActorLocation());

	bIsFetus ?
		Interactables_MainInteractable->SetActorRotation(TargetPoints_MainLocations[LocationIndex]->GetActorRotation() + FRotator(0,-90,0)) :
		Interactables_MainInteractable->SetActorRotation(TargetPoints_MainLocations[LocationIndex]->GetActorRotation());

	LocationIndex++;
	Interactables_MainInteractable->SetAudioToPlay(SFX_AlexTalk[LocationIndex]);
	
	 LightsOn();
}

//----------------------------------------------------------------------------------------------------------------------
void AHideAndSeekPuzzle::LightsOff()
{
	for (auto Element : Lights_NeededLights)
	{
		Element->TurnOff();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AHideAndSeekPuzzle::LightsOn()
{
	FTimerHandle Timer_LightsOut;
	
	if (!GetWorld()->GetTimerManager().IsTimerActive(Timer_LightsOut))
	{
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([&]
		{
			for (auto Element : Lights_NeededLights)
			{
				Element->TurnOn();
			}
			
			PlayerLighterStateSetter(true);
		});
				
		GetWorld()->GetTimerManager().SetTimer(Timer_LightsOut, timerDelegate, 1.5f, false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AHideAndSeekPuzzle::PlayerLighterStateSetter(bool UseOfLighter)
{
	Player->ForceLighterOff();
	Player->SetPlayerOptions(false, UseOfLighter, false);
}

//----------------------------------------------------------------------------------------------------------------------
void AHideAndSeekPuzzle::InteractionFeedBack()
{
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(.5f, 1, false, true, false, true);
	
	UGameplayStatics::SpawnSound2D(GetWorld(),SFX_InteractionFX);

	UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake,Player->GetActorLocation(),0,1000);
}

//----------------------------------------------------------------------------------------------------------------------
void AHideAndSeekPuzzle::PuzzleCompleted()
{
	OnPuzzleComplete.Broadcast();
	
	PostProcesModifierClass->ModifyPostProcessValues(PostProcessModiferValue, 0);
	
	if(bLightsOnAfterCompleted)
		LightsOn();

	if(bDestroyInteractableAfterCompleted)
		Interactables_MainInteractable->Destroy();
	
	Destroy();
}
#pragma endregion