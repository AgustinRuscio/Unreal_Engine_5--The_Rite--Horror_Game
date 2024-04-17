#include "InOrdenSelectionPuzzleFlow.h"

#define PRINT(X) GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT(X)));

AInOrdenSelectionPuzzleFlow::AInOrdenSelectionPuzzleFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
}
	

void AInOrdenSelectionPuzzleFlow::AddStatuette(AInteractor* currentStatuette)
{
	StatuettsAuxiliaryArray.Add(Cast<AStatuette>(currentStatuette));

	if(StatuettsAuxiliaryArray.Num() == InGameStatuettes.Num())
	{
		CheckStatuetteOrder();
		return;
	}
}

void AInOrdenSelectionPuzzleFlow::CheckStatuetteOrder()
{
	for (int i = 0; i < InGameStatuettes.Num(); ++i)
	{
		if((InGameStatuettes[i] != StatuettsAuxiliaryArray[i]))
		{
			PuzzleFailure();
			return;
		}
	}

	Destroy();
	PRINT("Complete");
}

void AInOrdenSelectionPuzzleFlow::PuzzleFailure()
{
	StatuettsAuxiliaryArray.Empty();

	for (auto Element : InGameStatuettes)
	{
		Element->RestoreInitialValues();
	}
	
	PRINT("Failure");
}

void AInOrdenSelectionPuzzleFlow::BeginPlay()
{
	Super::BeginPlay();

	for (auto Element : InGameStatuettes)
	{
		Element->OnInteractionTrigger.AddDynamic(this, &AInOrdenSelectionPuzzleFlow::AddStatuette);
	}
}