//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "SimpleCorridorFlow.h"

#include "Animation/SkeletalMeshActor.h"
#include "Components/AudioComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/AmbientSound.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/AmbientObjects/Manikin.h"
#include "TheRite/AmbientObjects/TriggererObject.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/LevelsGameFlow/ProsProcessModifier.h"
#include "TheRite/LevelsGameFlow/Puzzles/FetchInOrderPuzzle.h"
#include "TheRite/Triggers/DoorSlapper.h"
#include "TheRite/Triggers/TimerSound.h"

//----------------------------------------------------------------------------------------------------------------------
ASimpleCorridorFlow::ASimpleCorridorFlow()
{
	PrimaryActorTick.bCanEverTick = true;
	AudioComp = CreateDefaultSubobject<UAudioComponent>("Audio Comp");
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::BeginPlay()
{
	Super::BeginPlay();

	for (auto Element : PuzzleWalls)
	{
		Element->GetStaticMeshComponent()->SetVisibility(false);
		Element->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	BindTriggers();
	BindInteractables();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandleEnd);
	}

	if(TimerDelegateEnd.IsBound())
	{
		TimerDelegateEnd.Unbind();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::BindInteractables()
{
	EndInteractable->OnInteractionTrigger.AddDynamic(this, &ASimpleCorridorFlow::OnFetchPuzzleStarted);
	FetchPuzzle->OnPuzzleComplete.AddDynamic(this, &ASimpleCorridorFlow::OnFetchPuzzleFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::BindTriggers()
{
	TriggerEnableManikin->OnActorBeginOverlap.AddDynamic(this, &ASimpleCorridorFlow::OnTriggerBeginEnableAmbientInteractions);
	TriggerOutSideEnd->OnActorBeginOverlap.AddDynamic(this, &ASimpleCorridorFlow::OnTriggerBeginOutSideEnd);

	DoorSlapperHangedMan->OnSlappedDoor.AddDynamic(this, &ASimpleCorridorFlow::OnTriggerBeginDoorSlapperHangedMan);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnFetchPuzzleStarted(AInteractor* Interactable)
{
	PuzzleFeedBack(true);
	SFX_PuzzleClueLocation->Play();
	
	for (auto Element : PuzzleWalls)
	{
		Element->GetStaticMeshComponent()->SetVisibility(true);
		Element->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	for (auto Element : InitialDoors)
	{
		Element->HardClosing();
	}

	FetchPuzzle->ActivatePuzzle();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnFetchPuzzleFinished()
{
	bPuzzleEnd = true;

	
	PostProcessModifier->ModifyPostProcessValues(PostProcessModiferValue, .75f);
	
	SFX_PuzzleClueLocation->Destroy();
	
	AudioComp->Play();

	for (auto Element : PuzzleWalls)
	{
		Element->Destroy();
	}
	
	TimerSound->Destroy();
	
	//for (auto Element : InitialDoors)
	//{
	//	Element->SetLockedState(false);
	//	Element->Open();
	//}

	
	for (auto Element : AllLights)
	{
		Element->SetAggressiveMaterial();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::PuzzleFeedBack(bool bFeedBackOn)
{
	if(bFeedBackOn)
	{
		for (auto Element : AmbientSoundsOnPuzzle)
		{
			Element->Play();
		}

		PostProcessModifier->ModifyPostProcessValues(PostProcessModiferValue, .25f);
	}
	else
	{
		for (auto Element : AmbientSoundsOnPuzzle)
		{
			Element->Stop();
		};
		
		PostProcessModifier->ModifyPostProcessValues(PostProcessModiferValue, 0.f);
	}
	
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake_Puzzle,UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(),0,1000);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnTriggerBeginEnableAmbientInteractions(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;

	Manikin->Activate();
	TimerSound->Activate();
	
	TriggerEnableManikin->Destroy();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnTriggerBeginOutSideEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!bPuzzleEnd) return;

	PuzzleFeedBack(false);

	UGameplayStatics::PlaySound2D(GetWorld(), ZoneCompleted);

	for (auto Element : AllLights)
	{
		Element->SetNormalMaterial();
	}
	
	for (auto Element : AmbientSoundsOnPuzzle)
	{
		Element->Destroy();
	};
	
	AudioComp->Stop();
	AudioComp->DestroyComponent();

	TriggerOutSideEnd->Destroy();
	Manikin->Destroy();
	Destroy();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnTriggerBeginDoorSlapperHangedMan()
{
	TriggererObjectWheelChair->Activate();
}