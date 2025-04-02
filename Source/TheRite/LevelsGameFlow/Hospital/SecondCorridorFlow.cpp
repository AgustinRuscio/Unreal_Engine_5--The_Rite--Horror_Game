//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "SecondCorridorFlow.h"
#include "LightsPuzzle.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Math/UnrealMathUtility.h"

namespace 
{
	FVector FinalInteractorLocation;
}

//----------------------------------------------------------------------------------------------------------------------
ASecondCorridorFlow::ASecondCorridorFlow()
{
	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::BeginPlay()
{
	Super::BeginPlay();

	LightsPuzzle->OnPuzzleComplete.AddDynamic(this, &ASecondCorridorFlow::OnLightsPuzzleCompleted);

	//------- Glass Col timeline
	FOnTimelineFloat MoveInteractorTimelineCallback;
	MoveInteractorTimelineCallback.BindUFunction(this, FName("MoveInteractorTick"));
	TimeLineMoveInteractor.AddInterpFloat(CurveFloatMoveLightsKeyInteractor, MoveInteractorTimelineCallback);

	FOnTimelineEventStatic MoveInteractorTimelineFinishedCallback;
	MoveInteractorTimelineFinishedCallback.BindUFunction(this, FName("MoveInteractorFinished"));
	TimeLineMoveInteractor.SetTimelineFinishedFunc(MoveInteractorTimelineFinishedCallback);

	FinalInteractorLocation = KeyLightsObject->GetActorLocation() + LocationToAddToLightsPuzzleInteractor;
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::Tick(float DeltaSeconds)
{
	TimeLineMoveInteractor.TickTimeline(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::OnLightsPuzzleCompleted()
{
	KeyLightsObject->SetCanInteract(false);
	TimeLineMoveInteractor.PlayFromStart();

	OnLightsPuzzleCompletedFeedBack();
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::OnLightsPuzzleCompletedFeedBack()
{
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::MoveInteractorTick(float DeltaSeconds)
{
	auto LerpedLoction = FMath::Lerp(KeyLightsObject->GetActorLocation(), FinalInteractorLocation, DeltaSeconds);

	KeyLightsObject->SetActorLocation(LerpedLoction);
}

//----------------------------------------------------------------------------------------------------------------------
void ASecondCorridorFlow::MoveInteractorFinished(float DeltaSeconds)
{ }