//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "FetchInOrderPuzzle.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AFetchInOrderPuzzle::AFetchInOrderPuzzle()
{
	PrimaryActorTick.bCanEverTick = true;

	bActive			   = false;
	bFirstInteraction  = true;
	MaxObjectsPerRound = 8;
	Player			   = nullptr;

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
	bActive = true;
	
	ReLocateObjects();
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
		map.Add(Element, Element->GetActorLocation());
	}

//------
	
	for (auto Element : PossiblePosition)
	{
		AUXPossiblePosition.Add(Element);
	}

	if(MaxObjectsPerRound > AllObjects.Num() -1)
		MaxObjectsPerRound = AllObjects.Num() -1;
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(LightsOn_TimerHandle);
	LightsOn_TimerDelegate.Unbind();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::InteractionFeedBack()
{
	LightsOut();
	
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
	for (auto Element : map)
	{
		Element.Key->SetActorLocation(Element.Value);
	}
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Puzzle Steps
void AFetchInOrderPuzzle::ResetPuzzle(AInteractor* Interactable)
{
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
	
	ReLocateObjects();
	
	LightsOn();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::CheckNextPuzzleStep(AInteractor* Interactable)
{
	InteractionFeedBack();

	OffsetLightsOn = SFX_CorrectInteraction->GetDuration();
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_CorrectInteraction);

	TotalPuzzleSteps++;
	
	TotalPuzzleSteps == CorrectObjects.Num() ? PuzzleComplete() : NextStep();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::NextStep()
{
	if(bFirstInteraction)
	{
		bFirstInteraction = false;
	}
	
	ReLocateObjects();
	
	LightsOn();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::PuzzleComplete()
{
	OnPuzzleComplete.Broadcast();

	for (auto Element : RegularObjects)
	{
		Element->Destroy();
	}

	for (auto Element : CorrectObjects)
	{
		Element->Destroy();
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
		
		Element->SetActorLocation(newPos->GetActorLocation());
		Element->SetActorRotation(newPos->GetActorRotation() + FRotator(0,-90,0));
		
		auto EndAuxTarget = AUXPossiblePosition[AUXPossiblePosition.Num()-1];
		
		AUXPossiblePosition[AUXPossiblePosition.Num()-1] = newPos;
		AUXPossiblePosition[randomizer] = EndAuxTarget;
		
		AUXPossiblePosition.RemoveAt(AUXPossiblePosition.Num()-1);
	}

	AUXPossiblePosition.Empty();
	
	for (auto Element : PossiblePosition)
	{
		AUXPossiblePosition.Add(Element);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AFetchInOrderPuzzle::RemoveFirstRightObjects()
{
	auto currentFetus = AuxCorrectObjects[0];
	
	auto rand = FMath::RandRange(0, AUXPossiblePosition.Num() - 1);
	auto currentTarget = AUXPossiblePosition[rand];
		
	currentFetus->SetActorLocation(currentTarget->GetActorLocation());
	currentFetus->SetActorRotation(currentTarget->GetActorRotation()+ FRotator(0,-90,0));
		
	auto EndAuxTarget = AUXPossiblePosition[AUXPossiblePosition.Num()-1];
	AUXPossiblePosition[AUXPossiblePosition.Num()-1] = currentTarget;
	AUXPossiblePosition[rand] = EndAuxTarget;
	AUXPossiblePosition.RemoveAt(AUXPossiblePosition.Num()-1);


	auto EndAuxFetus = AuxCorrectObjects[AuxCorrectObjects.Num()-1];
	AuxCorrectObjects[AuxCorrectObjects.Num()-1] = currentFetus;
	AuxCorrectObjects[0] = EndAuxFetus;
	AuxCorrectObjects.RemoveAt(AuxCorrectObjects.Num()-1);
}
#pragma endregion