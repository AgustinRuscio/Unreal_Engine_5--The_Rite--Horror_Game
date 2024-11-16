//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "SimpleCorridorFlow.h"

#include "BackCorridorFlow.h"
#include "Components/AudioComponent.h"
#include "Components/LightComponent.h"
#include "Engine/SpotLight.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/AmbientSound.h"
#include "TheRite/AmbientObjects/AppearanceEvent.h"
#include "TheRite/AmbientObjects/CustomLight.h"
#include "TheRite/AmbientObjects/CyclicAudios.h"
#include "TheRite/AmbientObjects/Manikin.h"
#include "TheRite/AmbientObjects/TriggererObject.h"
#include "TheRite/AmbientObjects/WalkerTiffany.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/LevelsGameFlow/ProsProcessModifier.h"
#include "TheRite/LevelsGameFlow/Puzzles/FetchInOrderPuzzle.h"
#include "TheRite/Triggers/DoorScaryKnocking.h"
#include "TheRite/Triggers/TimerSound.h"

static float HintLightInitialIntensity;

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

	Emblem->OnInteractionTrigger.AddDynamic(this, &ASimpleCorridorFlow::ActivateWalk);
	AppearanceInteractable->OnInteractionTrigger.AddDynamic(this, &ASimpleCorridorFlow::CallBackForAppearanceEvent);
	HangedManAppearance->OnAppearanceEventEndStart.AddDynamic(this, &ASimpleCorridorFlow::LightsOff);
	HangedManAppearance->OnAppearanceEventEndEnd.AddDynamic(this, &ASimpleCorridorFlow::LightsOn);

	HintLightInitialIntensity = HintSpotlight->GetLightComponent()->Intensity;
	
	BindTriggers();
	BindInteractables();
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

	DoorSlapperHangedMan->OnTriggerActivatedDelegate.AddDynamic(this, &ASimpleCorridorFlow::OnTriggerBeginDoorSlapperHangedMan);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::ActivateWalk(AInteractor* interactor)
{
	Walker->Activate();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::CallBackForAppearanceEvent(AInteractor* interactor)
{
	HangedManAppearance->MakeAppear();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::LightsOn()
{
	HintSpotlight->GetLightComponent()->SetIntensity(HintLightInitialIntensity);
	
	for (auto Element : AllLights2)
	{
		Element->TurnOn();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::LightsOff()
{
	HintSpotlight->GetLightComponent()->SetIntensity(0);

	for (auto Element : AllLights2)
	{
		Element->TurnOff();
	}
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

	for (auto Element : CyclicAudios)
	{
		Element->Activate();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnFetchPuzzleFinished()
{
	bPuzzleEnd = true;

	PostProcessModifier->ModifyPostProcessValues(PostProcessModiferValue, .5f);

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

	for (auto Element : AllLights2)
	{
		Element->SetAggressiveMaterial();
	}

	for (auto Element : CyclicAudios)
	{
		Element->Destroy();
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

		PostProcessModifier->ModifyPostProcessValues(PostProcessModiferValue, .1f);
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

	for (auto Element : AllLights2)
	{
		Element->SetNormalMaterial();
	}
	
	for (auto Element : AmbientSoundsOnPuzzle)
	{
		Element->Destroy();
	};

	for (auto Element : SecondPuzzleDoors)
	{
		Element->SetLockedState(false);
	};
	
	AudioComp->Stop();
	AudioComp->DestroyComponent();

	TriggerOutSideEnd->Destroy();
	Manikin->Destroy();
	NextPuzzle->ActivateZone();
	Destroy();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleCorridorFlow::OnTriggerBeginDoorSlapperHangedMan()
{
	TriggererObjectWheelChair->Activate();
}