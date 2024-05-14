//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "InOrdenSelectionPuzzleFlow.h"

#include "Engine/TargetPoint.h"
#include "TheRite/Interactuables/AltarWhell.h"
#include "TheRite/Interactuables/Altar.h"
#include "TheRite/Interactuables/Statuette.h"
#include "TheRite/Interactuables/Interactor.h"

#define PRINTONVIEWPORT(X) GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT(X)));

AInOrdenSelectionPuzzleFlow::AInOrdenSelectionPuzzleFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
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

//---------------- Check puzzle Methods
bool AInOrdenSelectionPuzzleFlow::CheckStatuttes()
{
	for (int i = 0; i < InGameStatuettes.Num(); ++i)
	{
		if((InGameStatuettes[i] != StatuettsAuxiliaryArray[i]))
		{
			PRINTONVIEWPORT("Statuette Fail");
			PuzzleFailure();
			return false;
		}
	}

	return true;
}

bool AInOrdenSelectionPuzzleFlow::CheckRotation()
{
	for (auto Element : AltarWhells)
	{
		if(!Element->CheckRotation())
		{
			PRINTONVIEWPORT("Whell Fail");
			PuzzleFailure();
			return false;
		}
	}
	
	return true;
}

void AInOrdenSelectionPuzzleFlow::CheckStatuetteOrder()
{
	if (!GetWorldTimerManager().IsTimerActive(OffSetInteraction))
	{
		FTimerDelegate timerDelegate;
		
		timerDelegate.BindLambda([&]
		{
			if(!CheckStatuttes() || !CheckRotation())
			{
				PuzzleFailure();
				return;
			}
	
			OnPuzzleFinished.Broadcast();

			for (auto Element : AltarWhells)
			{
				Element->DisableInteraction();
			}

			Altar->DisableAltarInteraction();
			Destroy();
			PRINTONVIEWPORT("Complete");
		});
			
		GetWorldTimerManager().SetTimer(OffSetInteraction, timerDelegate, 1.f, false);
	}
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

//----------------
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