//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "MorguePuzzleFlow.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/AmbientObjects/CustomLight.h"
#include "Engine/TargetPoint.h"
#include "Engine/TriggerBox.h"
#include "Engine/StaticMeshActor.h"
#include <Kismet/GameplayStatics.h>

namespace
{
	FTransform BodyOneOriginalLocation;
	FTransform BodyTwoOriginalLocation;
}

//----------------------------------------------------------------------------------------------------------------------
AMorguePuzzleFlow::AMorguePuzzleFlow()
{
	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::BeginPlay()
{
	Super::BeginPlay();

	TurnLightsOnTimerDelegate.BindLambda([this]
		{
			for (auto current : AllLights)
			{
				current->TurnOn();
			}
		});

	BodyOneOriginalLocation = DeadBodyOne->GetActorTransform();
	BodyTwoOriginalLocation = DeadBodyTwo->GetActorTransform();

	Emblem->OnInteractionTrigger.AddDynamic(this, &AMorguePuzzleFlow::OnEmblemInteraction);
	EndTriggerBox->OnActorBeginOverlap.AddDynamic(this, &AMorguePuzzleFlow::BeginOverlap);
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	TurnLightsOnTimerDelegate.Unbind();
	TurnLightsOnTimerHandle.Invalidate();
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::TurnLightsOff()
{
	for (auto current : AllLights)
	{
		current->TurnOff();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::LightsOnOff()
{
	TurnLightsOff();

	for (auto current : SFX_LightsOff)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), current);
	}

	GetWorld()->GetTimerManager().SetTimer(TurnLightsOnTimerHandle, TurnLightsOnTimerDelegate, 1.5f, false);
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::OnEmblemInteraction(AInteractor* interactor)
{
	bEmpblemObtain = true;

	LightsOnOff();

	DeadBodyOne->SetActorTransform(DeadBodyOneTargetPoint->GetActorTransform());
	DeadBodyTwo->SetActorTransform(DeadBodyTwoTargetPoint->GetActorTransform());
}

void AMorguePuzzleFlow::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!bEmpblemObtain) return;
	LightsOnOff();

	DeadBodyOne->SetActorTransform(BodyOneOriginalLocation);
	DeadBodyTwo->SetActorTransform(BodyTwoOriginalLocation);
}