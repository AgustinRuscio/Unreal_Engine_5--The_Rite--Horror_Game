//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "MorguePuzzleFlow.h"
#include "TheRite/Interactuables/DeathTiffany.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/AmbientObjects/CustomLight.h"
#include "Engine/TargetPoint.h"
#include "Engine/TriggerBox.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/DirectionalLight.h"
#include <Kismet/GameplayStatics.h>

namespace
{
	FTransform BodyOneOriginalLocation;
	FTransform BodyTwoOriginalLocation;
}

//----------------------------------------------------------------------------------------------------------------------
AMorguePuzzleFlow::AMorguePuzzleFlow()
{
	PrimaryActorTick.bCanEverTick = false;
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

	Pillow->OnInteractionTrigger.AddDynamic(this, &AMorguePuzzleFlow::OnPillowInteraction);

	Emblem->OnInteractionTrigger.AddDynamic(this, &AMorguePuzzleFlow::OnEmblemInteraction);

	DeathTiff->OnInteractionTrigger.AddDynamic(this, &AMorguePuzzleFlow::OnDeathTiffInteraction);

	EndTriggerBox->OnActorBeginOverlap.AddDynamic(this, &AMorguePuzzleFlow::BeginOverlap);

	Emblem->Dissapear();
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(TurnLightsOnTimerDelegate.IsBound())
		TurnLightsOnTimerDelegate.Unbind();

	if (TurnLightsOnTimerHandle.IsValid())
		TurnLightsOnTimerHandle.Invalidate();

	if(TurnLightsOffTimerDelegate.IsBound())
		TurnLightsOffTimerDelegate.Unbind();

	if (TurnLightsOffTimerHandle.IsValid())
		TurnLightsOffTimerHandle.Invalidate();
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::TurnLightsOff()
{
	for (auto current : AllLights)
	{
		current->TurnOff();
	}
	DirectionLight->SetActorHiddenInGame(true);
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

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::OnDeathTiffInteraction(AInteractor* interactor)
{
	TurnLightsOff();

	TurnLightsOffTimerDelegate.BindLambda([this]
		{
			for (auto current : AllLights)
			{
				current->TurnOn();
			}

			DirectionLight->SetActorHiddenInGame(false);
			Emblem->Appear();

		});

	GetWorld()->GetTimerManager().SetTimer(TurnLightsOffTimerHandle, TurnLightsOffTimerDelegate, 1.5f, false);


	for (auto obj : DoorsToBeClose)
	{
		obj->HardClosing();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::OnPillowInteraction(AInteractor* interactor)
{
	DeathTiff->SetPillowReady(Pillow->GetItemName(), Pillow->GetItemID());
}

//----------------------------------------------------------------------------------------------------------------------
void AMorguePuzzleFlow::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!bEmpblemObtain) return;
	LightsOnOff();

	DeadBodyOne->SetActorTransform(BodyOneOriginalLocation);
	DeadBodyTwo->SetActorTransform(BodyTwoOriginalLocation);

	EndTriggerBox->OnActorBeginOverlap.RemoveDynamic(this, &AMorguePuzzleFlow::BeginOverlap);
	EndTriggerBox->Destroy();
}