//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "MorguePuzzle.h"
#include "TheRite/AmbientObjects/CustomLight.h"
#include "TheRite/Interactuables/Coffin.h"
#include <Kismet/GameplayStatics.h>

//----------------------------------------------------------------------------------------------------------------------
AMorguePuzzle::AMorguePuzzle()
{
	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzle::BeginPlay()
{ 
	Super::BeginPlay();

	for (auto current : AllCoffins)
	{
		current->OnInteractionTrigger.AddDynamic(this, &AMorguePuzzle::OnCoffinOppened);
		current->CoffinOpening.AddDynamic(this, &AMorguePuzzle::CoffinOpened);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzle::OnCoffinOppened(class AInteractor* Interactor)
{
	for (auto current : AllCoffins)
	{
		current->SetCanInteract(true);
	}

	auto castedCoffin = CastChecked<ACoffin>(Interactor);

	if (castedCoffin->IsCoffinOpen())
	{
		OpenCoffins.Add(castedCoffin);
	}
	else
	{
		if (OpenCoffins.Contains(castedCoffin))
			OpenCoffins.Remove(castedCoffin);
	}

	CheckPuzzleStatus();
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzle::CheckPuzzleStatus()
{
	if (OpenCoffins.Num() != CorrectCoffins.Num()) return;

	for (auto current : OpenCoffins)
	{
		if (!CorrectCoffins.Contains(current)) return;
	}

	OnPuzzleCompleted();
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzle::CoffinOpened()
{
	for (auto current : AllCoffins)
	{
		current->SetCanInteract(false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzle::OnPuzzleCompleted()
{
	for (auto current : AllCoffins)
	{
		current->SetCanInteract(false);
	}

	PuzzleCompleteFeedBack();

	LastCoffin->ForceCoffinOpenning();
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzle::PuzzleCompleteFeedBack()
{
	for (auto current : FeedbackLights)
	{
		current->ChangeLightIntensity(NewLightIntensity, false);
		current->SetIntermitentMaterial();
	}

	for (auto current : EndPuzzleSFX)
	{
		UGameplayStatics::PlaySound2D(this, current);
	}
}