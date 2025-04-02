//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InOrdenSelectionPuzzleFlow.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleFinished);

class AStatuette;
class AInteractor;
class ATargetPoint;
class AAltarWhell;
class AAltar;
class AStaticMeshActor;

UCLASS()
class THERITE_API AInOrdenSelectionPuzzleFlow : public AActor
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AInOrdenSelectionPuzzleFlow();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnPuzzleFinished OnPuzzleFinished;

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bEnableDoOnce = true;

	int8 MaxStatuatte;
	int8 StatuatteIndex;

	UPROPERTY(EditAnywhere, Category = "Puzzle objects")
	TArray<AStaticMeshActor*> AltarBases;
	
	FTimerHandle OffSetInteraction;
	
	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* AlexAudio;
	
	UPROPERTY(EditAnywhere, Category="TargetPoints")
	TArray<ATargetPoint*> AltarPositions;
	
	UPROPERTY(EditAnywhere, Category = "Puzzle objects")
	TArray<AAltarWhell*> AltarWhells;
	
	UPROPERTY(EditAnywhere, Category = "Puzzle objects")
	TArray<AStatuette*> InGameStatuettes;
	TArray<AStatuette*> StatuettsAuxiliaryArray;

	UPROPERTY(EditAnywhere, Category = "Puzzle objects")
	AAltar* Altar;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	
	//---------------- Check puzzle Methods
	bool CheckStatuttes();
	bool CheckRotation();
	
	void CheckStatuetteOrder();
	void PuzzleFailure();
	
	UFUNCTION()
	void AddStatuette(AInteractor* currentStatuette);	
};