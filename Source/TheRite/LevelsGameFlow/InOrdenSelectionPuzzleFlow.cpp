//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "InOrdenSelectionPuzzleFlow.h"

#include "Engine/TargetPoint.h"
#include "TheRite/Interactuables/AltarWhell.h"
#include "TheRite/Interactuables/Statuette.h"
#include "TheRite/Interactuables/Interactor.h"

#define PRINTONVIEWPORT(X) GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT(X)));

AInOrdenSelectionPuzzleFlow::AInOrdenSelectionPuzzleFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
}
	

void AInOrdenSelectionPuzzleFlow::AddStatuette(AInteractor* currentStatuette)
{
	auto CurrentStatuette = Cast<AStatuette>(currentStatuette);

	if(StatuatteIndex == InGameStatuettes.Num()-1 && bEnableDoOnce)
	{
		for (auto Element : InGameStatuettes)
		{
			Element->EnableInteraction();
		}

		for (auto Element : AltarWhells)
		{
			Element->EnableInteraction();
		}
		
		bEnableDoOnce = false;
	}
	
	if(CurrentStatuette->IsFirstInteraction())
	{
		CurrentStatuette->SetAltarPosition(AltarPositions[StatuatteIndex]->GetActorLocation(), AltarPositions[StatuatteIndex]->GetActorRotation());
		AltarWhells[StatuatteIndex]->ASignValues(CurrentStatuette, CurrentStatuette->GetDesiredRotation(), CurrentStatuette->GetRotatioToAdd());
		AltarWhells[StatuatteIndex]->StatuetteReady();
		
		++StatuatteIndex;
	}
	else
	{
		for (auto Element : AltarWhells)
		{
			Element->DisableInteraction();
		}
		
		StatuettsAuxiliaryArray.Add(CurrentStatuette);
		
		if(StatuettsAuxiliaryArray.Num() == InGameStatuettes.Num())
		{
			CheckStatuetteOrder();
		}
	}
}

void AInOrdenSelectionPuzzleFlow::CheckStatuetteOrder()
{
	for (int i = 0; i < InGameStatuettes.Num(); ++i)
	{
		if((InGameStatuettes[i] != StatuettsAuxiliaryArray[i]))
		{
			UE_LOG(LogTemp, Warning, TEXT("Statuette"));
			PuzzleFailure();
			return;
		}
	}

	for (auto Element : AltarWhells)
	{
		if(!Element->CheckRotation())
		{
			UE_LOG(LogTemp, Warning, TEXT("Whell"));
			PuzzleFailure();
			return;
		}
	}
	

	OnPuzzleFinished.Broadcast();
	Destroy();
	PRINTONVIEWPORT("Complete");
}

void AInOrdenSelectionPuzzleFlow::PuzzleFailure()
{
	StatuettsAuxiliaryArray.Empty();

	for (auto Element : InGameStatuettes)
	{
		Element->RestoreInitialValues();
	}

	for (auto Element : AltarWhells)
	{
		Element->EnableInteraction();
	}
	
	PRINTONVIEWPORT("Failure");
}

void AInOrdenSelectionPuzzleFlow::BeginPlay()
{
	Super::BeginPlay();

	for (auto Element : InGameStatuettes)
	{
		Element->OnInteractionTrigger.AddDynamic(this, &AInOrdenSelectionPuzzleFlow::AddStatuette);
	}

	MaxStatuatte = InGameStatuettes.Num();
}