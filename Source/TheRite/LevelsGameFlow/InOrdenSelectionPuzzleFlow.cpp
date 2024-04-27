//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "InOrdenSelectionPuzzleFlow.h"

#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"
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
		
		bEnableDoOnce = false;
	}
	
	if(CurrentStatuette->IsFirstInteraction())
	{
		CurrentStatuette->SetAltarPosition(AltarPositions[StatuatteIndex]->GetActorLocation(), AltarPositions[StatuatteIndex]->GetActorRotation());
		++StatuatteIndex;
	}
	else
	{
		StatuettsAuxiliaryArray.Add(CurrentStatuette);
		
		if(StatuettsAuxiliaryArray.Num() == InGameStatuettes.Num())
		{
			CheckStatuetteOrder();
		}
		else
		{
			auto player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

			//player->ForceTalk(AlexAudio);
		}
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
	PRINTONVIEWPORT("Complete");
}

void AInOrdenSelectionPuzzleFlow::PuzzleFailure()
{
	StatuettsAuxiliaryArray.Empty();

	for (auto Element : InGameStatuettes)
	{
		Element->RestoreInitialValues();
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