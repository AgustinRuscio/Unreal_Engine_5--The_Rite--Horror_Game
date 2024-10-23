//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "FetchInOrderPuzzle.h"

#include "Components/LightComponent.h"
#include "Engine/SpotLight.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/AmbientObjects/ChangingActor.h"
#include "TheRite/Characters/Alex.h"

static float OriginalLightIntensity;

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AFetchInOrderPuzzle::AFetchInOrderPuzzle()
{
	PrimaryActorTick.bCanEverTick = true;

	bActive				 	= false;
	bFirstInteraction	 	= true;
	MaxObjectsPerRound	 	= 8;
	TotalPuzzleSteps	 	= 0;
	ChangingObjectsIndex 	= -1;

	Player					= nullptr;
	SFX_CorrectInteraction	= nullptr;
	SFX_WrongInteraction	= nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
bool AFetchInOrderPuzzle::IsActive() const
{
	return bActive;
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::SetPuzzleState(bool NewPuzzleState)
{
	bActive = NewPuzzleState;
}

void AFetchInOrderPuzzle::ActivatePuzzle()
{
	bActive				 = true;
	ChangingObjectsIndex = 0;

	OriginalLightIntensity = AllLights[0]->GetIntensity();

	for (auto Element : AllLights)
	{
		Element->ChangeLightIntensity(70.f, true);
	}

	Player->SetPlayerOptions(true, true, false);
	Player->ForceTurnLighterOn();

	ClueLight->GetLightComponent()->SetIntensity(150.f);
	
	LightsOut();
	
	for (auto Element : ChangingActors)
	{
		Element->ChangeObjectVisuals(FeedbackInfo[ChangingObjectsIndex].GetNextMaterial(), FeedbackInfo[ChangingObjectsIndex].GetNextMesh());
	}
	
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(.5f, 1, false, true, false, true);
	
	ReLocateObjects();

	OffsetLightsOn = SFX_WrongInteraction->GetDuration();
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_WrongInteraction);
	
	LightsOn();
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::BeginPlay()
{	
	Super::BeginPlay();

	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
//----- New objects
	for (auto Element : RegularObjects)
	{
		Element->OnInteractionTrigger.AddDynamic(this, &AFetchInOrderPuzzle::ResetPuzzle);
		AllObjects.Add(Element);
	}
	
	for (auto Element : CorrectObjects)
	{
		Element->OnInteractionTrigger.AddDynamic(this, &AFetchInOrderPuzzle::CheckNextPuzzleStep);
		AllObjects.Add(Element);
		AuxCorrectObjects.Add(Element);
	}

	for (auto Element : AllObjects)
	{
		MapObjectsAndLocations.Add(Element, Element->GetActorLocation());
	}

//------
	
	for (auto Element : PossiblePosition)
	{
		AUXPossiblePosition.Add(Element);
	}

	for (auto Element : RoomsSpotLights)
	{
		Element->GetLightComponent()->SetIntensity(0.f);
		AUXRoomsSpotLights.Add(Element);
	}

	ClueLight->GetLightComponent()->SetIntensity(0.f);

	
	if(MaxObjectsPerRound > AllObjects.Num() -1)
		MaxObjectsPerRound = AllObjects.Num() -1;
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(LightsOn_TimerHandle);
	GetWorldTimerManager().ClearTimer(LightsWit);
	LightsOn_TimerDelegate.Unbind();
}

void AFetchInOrderPuzzle::PrepareTargets()
{
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::InteractionFeedBack()
{
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(.5f, 1, false, true, false, true);
	
	LightsOut();

	for (auto Element : ChangingActors)
	{
		Element->ChangeObjectVisuals(FeedbackInfo[ChangingObjectsIndex].GetNextMaterial(), FeedbackInfo[ChangingObjectsIndex].GetNextMesh());
	}

	for (auto Element : SpotlightsTurnedOn)
	{
		Element->GetLightComponent()->SetIntensity(0.f);
	}
	SpotlightsTurnedOn.Empty();

	AUXRoomsSpotLights.Empty();
	for (auto Element : RoomsSpotLights)
	{
		AUXRoomsSpotLights.Add(Element);
	}
	
	Player->ForceLighterOff();
	//Player->SetPlayerOptions(false, false, false);

	for (auto Element : RegularObjects)
	{
		Element->SetCanInteract(false);
	}
	for (auto Element : CorrectObjects)
	{
		Element->SetCanInteract(false);
	}
	
	ResetObjects();
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Lights Manipulation Methods
void AFetchInOrderPuzzle::LightsOut()
{
	for (auto Element : AllLights)
	{
		Element->TurnOff();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::LightsOn()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(LightsOn_TimerHandle))
	{
		LightsOn_TimerDelegate.BindLambda([&]
		{
			for (auto Element : AllLights)
			{
				Element->TurnOn();
			}

			for (auto Element : AllObjects)
			{
				Element->SetCanInteract(true);
			}
		});
		
		GetWorld()->GetTimerManager().SetTimer(LightsOn_TimerHandle, LightsOn_TimerDelegate, OffsetLightsOn, false);
	}
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::ResetObjects()
{
	for (auto Element : MapObjectsAndLocations)
	{
		Element.Key->SetActorLocation(Element.Value);
	}
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Puzzle Steps
void AFetchInOrderPuzzle::ResetPuzzle(AInteractor* Interactable)
{
	ChangingObjectsIndex = 0;

	UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake_WrongObject,Player->GetActorLocation(),0,1000);
	InteractionFeedBack();

	OffsetLightsOn = SFX_WrongInteraction->GetDuration();
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_WrongInteraction);
	
	bFirstInteraction = true;

	AuxCorrectObjects.Empty();
	
	for (auto Element : CorrectObjects)
	{
		AuxCorrectObjects.Add(Element);
	}

	TotalPuzzleSteps = 0;

	if (!GetWorld()->GetTimerManager().IsTimerActive(LightsWit))
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([&]
		{
			ReLocateObjects();
			LightsOn();
		});
		
		float time = OffsetLightsOn - (OffsetLightsOn*.5f);
		GetWorld()->GetTimerManager().SetTimer(LightsWit, TimerDelegate, time, false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::CheckNextPuzzleStep(AInteractor* Interactable)
{
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake_CorrectObject,Player->GetActorLocation(),0,1000);

	++ChangingObjectsIndex;

	if(ChangingObjectsIndex >= FeedbackInfo.Num())
	{
		ChangingObjectsIndex = FeedbackInfo.Num()-1;
	}

	OffsetLightsOn = SFX_CorrectInteraction->GetDuration();
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_CorrectInteraction);

	TotalPuzzleSteps++;
	
	TotalPuzzleSteps == CorrectObjects.Num() ? PuzzleComplete() : NextStep();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::NextStep()
{
	InteractionFeedBack();
	
	if(bFirstInteraction)
	{
		bFirstInteraction = false;
	}
	
	if (!GetWorld()->GetTimerManager().IsTimerActive(LightsWit))
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([&]
		{
			ReLocateObjects();
			LightsOn();
		});
		
		float time = OffsetLightsOn - (OffsetLightsOn*.5f);
		GetWorld()->GetTimerManager().SetTimer(LightsWit, TimerDelegate, time, false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::PuzzleComplete()
{
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(.5f, 1, false, true, false, true);
	
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake_WrongObject,Player->GetActorLocation(),0,1000);
	Player->SetPlayerOptions(true, false, false);
	Player->ForceLighterOff();
	
	OnPuzzleComplete.Broadcast();

	ClueLight->GetLightComponent()->SetIntensity(0.f);
	ClueLight->Destroy();

	for (auto Element : AllLights)
	{
		Element->ChangeLightIntensity(OriginalLightIntensity, true);
	}
	
	for (auto Element : RegularObjects)
	{
		Element->Destroy();
	}

	for (auto Element : RoomsSpotLights)
	{
		Element->Destroy();
	}
	AUXRoomsSpotLights.Empty();
	
	for (auto Element : CorrectObjects)
	{
		Element->Destroy();
	}
	
	for (auto Element : ChangingActors)
	{
		Destroy();
	}
	
	LightsOn_TimerDelegate.Unbind();
	GetWorldTimerManager().ClearTimer(LightsOn_TimerHandle);

	//Player->SetPlayerOptions(false, true, false);

	Destroy();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::ReLocateObjects()
{
	RemoveFirstRightObjects();
	
	int counter = 0;
	
	for (auto Element : RegularObjects)
	{
		if(counter >= MaxObjectsPerRound ||AUXPossiblePosition.Num() == 0) break;
		counter++;
		
		auto randomizer = FMath::RandRange(0, AUXPossiblePosition.Num() - 1);
		auto newPos = AUXPossiblePosition[randomizer];
		
		auto currentLight = AUXRoomsSpotLights[randomizer];
		currentLight->GetLightComponent()->SetIntensity(67.5f);
		SpotlightsTurnedOn.Add(currentLight);
		
		Element->SetActorLocation(newPos->GetActorLocation());
		Element->SetActorRotation(newPos->GetActorRotation() + FRotator(0,-90,0));
		
		auto EndAuxTarget = AUXPossiblePosition[AUXPossiblePosition.Num()-1];
		AUXPossiblePosition[AUXPossiblePosition.Num()-1] = newPos;
		AUXPossiblePosition[randomizer] = EndAuxTarget;
		AUXPossiblePosition.RemoveAt(AUXPossiblePosition.Num()-1);

		auto EndAuxLight = AUXRoomsSpotLights[AUXRoomsSpotLights.Num()-1];
		AUXRoomsSpotLights[AUXRoomsSpotLights.Num()-1] = currentLight;
		AUXRoomsSpotLights[randomizer] = EndAuxLight;
		AUXRoomsSpotLights.RemoveAt(AUXRoomsSpotLights.Num()-1);
		
	}

	AUXPossiblePosition.Empty();
	
	for (auto Element : PossiblePosition)
	{
		AUXPossiblePosition.Add(Element);
	}
	
	AUXRoomsSpotLights.Empty();
	
	for (auto Element : AUXRoomsSpotLights)
	{
		AUXRoomsSpotLights.Add(Element);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::RemoveFirstRightObjects()
{
	TArray<class ATargetPoint*> RandLocations;
	TArray<class ASpotLight*> RandLights;
	
	for (auto Element : AUXPossiblePosition)
	{
		if(Element == AUXLastCorrectTarget) continue;
		RandLocations.Add(Element);
	}

	for (auto Element : AUXRoomsSpotLights)
	{
		if(Element == AUXLastLight) continue;
		RandLights.Add(Element);
	}
	
	auto currentFetus = AuxCorrectObjects[0];
	
	auto rand = FMath::RandRange(0, RandLocations.Num() - 1);
	auto currentTarget = RandLocations[rand];
	
	auto currentLight = RandLights[rand];
	currentLight->GetLightComponent()->SetIntensity(67.5f);
	SpotlightsTurnedOn.Add(currentLight);
		
	currentFetus->SetActorLocation(currentTarget->GetActorLocation());
	currentFetus->SetActorRotation(currentTarget->GetActorRotation()+ FRotator(0,-90,0));
	
	AUXLastCorrectTarget = currentTarget;
	AUXLastLight = currentLight;
	
	//------  Realign AUX array
	auto EndAuxTarget = RandLocations[RandLocations.Num()-1];
	RandLocations[RandLocations.Num()-1] = currentTarget;
	RandLocations[rand] = EndAuxTarget;
	RandLocations.RemoveAt(RandLocations.Num()-1);

	AUXPossiblePosition.Empty();
	AUXPossiblePosition = RandLocations;

	auto EndAuxLight = RandLights[RandLights.Num()-1];
	RandLights[RandLights.Num()-1] = currentLight;
	RandLights[rand] = EndAuxLight;
	RandLights.RemoveAt(RandLights.Num()-1);

	AUXRoomsSpotLights.Empty();
	AUXRoomsSpotLights = RandLights;

	//------------

	auto EndAuxFetus = AuxCorrectObjects[AuxCorrectObjects.Num()-1];
	AuxCorrectObjects[AuxCorrectObjects.Num()-1] = currentFetus;
	AuxCorrectObjects[0] = EndAuxFetus;
	AuxCorrectObjects.RemoveAt(AuxCorrectObjects.Num()-1);
}
#pragma endregion