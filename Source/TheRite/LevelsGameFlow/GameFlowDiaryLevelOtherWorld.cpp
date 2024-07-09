//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "GameFlowDiaryLevelOtherWorld.h"
#include "InOrdenSelectionPuzzleFlow.h"
#include "Components/LightComponent.h"
#include "Engine/SpotLight.h"
#include "Engine/RectLight.h"
#include "Engine/TriggerVolume.h"
#include "TheRite/Interactuables/Door.h"
#include "Animation/SkeletalMeshActor.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/Characters/Alex.h"

AGameFlowDiaryLevelOtherWorld::AGameFlowDiaryLevelOtherWorld()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//---------------- System Class Methods
void AGameFlowDiaryLevelOtherWorld::BeginPlay()
{
	Super::BeginPlay();

	InitializeValues();
	BindTriggers();
	BindMethods();
}

//---------------- Initialize Methods
void AGameFlowDiaryLevelOtherWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameFlowDiaryLevelOtherWorld::BindTriggers()
{
	TriggerVolume_LivingRoomEvent->OnActorBeginOverlap.AddDynamic(this, &AGameFlowDiaryLevelOtherWorld::OnTriggerLivingRoomEventOverlap);
	TriggerVolume_KitchenEvent->OnActorBeginOverlap.AddDynamic(this, &AGameFlowDiaryLevelOtherWorld::OnTriggerKitchenEventOverlap);
	TriggerVolume_DinningEvent->OnActorBeginOverlap.AddDynamic(this, &AGameFlowDiaryLevelOtherWorld::OnTriggerDinningRoomEventOverlap);
	TriggerVolume_EndGamePass->OnActorBeginOverlap.AddDynamic(this, &AGameFlowDiaryLevelOtherWorld::OnTriggerEndGamePassOverlap);
}

void AGameFlowDiaryLevelOtherWorld::BindMethods()
{
	InOrderPOuzzleController->OnPuzzleFinished.AddDynamic(this, &AGameFlowDiaryLevelOtherWorld::EndGame);
}

void AGameFlowDiaryLevelOtherWorld::InitializeValues()
{
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	for (auto Element : EndGameWall)
	{
		Element->GetStaticMeshComponent()->SetVisibility(false);
		Element->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}

	
	for (auto Element : Skeletals_DinningRoomEvet)
	{
		Element->GetSkeletalMeshComponent()->SetVisibility(false);
	}

	for (auto Element : Lights_DinningEventLights)
	{
		Element->GetLightComponent()->SetIntensity(0);
	}
	
	InteractorEventDinningRoom->OnInteractionTrigger.AddDynamic(this, &AGameFlowDiaryLevelOtherWorld::DinningRoomObjectEventGrab);
}


void AGameFlowDiaryLevelOtherWorld::EndGame()
{
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_LastAudio);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_LightsOut);
	
	for (auto Element : Lights_AllLights)
	{
		Element->TurnOff();
	}
	
	for (auto Element : Candles_EndGame)
	{
		Element->TurnOn();
	}

	for (auto Element : EndGameWall)
	{
		Element->GetStaticMeshComponent()->SetVisibility(true);
		Element->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	}

	Doors_BathRoom->SetLockedState(true);
	Doors_BathRoom->HardClosing();
	
	Doors_BedRoom->SetLockedState(true);
	Doors_BedRoom->HardClosing();
	
	Doors_EndGame->SetLockedState(false);
	
	Player->ForceTurnLighterOn();
	Player->SetPlayerOptions(true, false, false);
}

void AGameFlowDiaryLevelOtherWorld::DinningRoomObjectEventGrab(AInteractor* a)
{
	if(bDinningRoomEventDone) return;
	
	bEventReadyDinningRoom = true;

	for (auto Element : Skeletals_DinningRoomEvet)
	{
		Element->GetSkeletalMeshComponent()->SetVisibility(true);
	}

	for (auto Element : Lights_DinningEventLights)
	{
		Element->GetLightComponent()->SetIntensity(20);
	}
	for (auto Element : Lights_AllLights)
	{
		if(Element->GetLightZone() != HouseZone::DiningRoom) continue;
		Element->TurnOff();
	}
}

//---------------- Bind Colliders Methods
void AGameFlowDiaryLevelOtherWorld::OnTriggerLivingRoomEventOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || bLivingRoomEventDone) return;
	bLivingRoomEventDone = true;
	
	for (auto Element : Lights_AllLights)
	{
		if(Element->GetLightZone() != HouseZone::LivingRoom) continue;
		Element->TurnOn();
	}

	auto controller = Cast<AAlexPlayerController>(Player->GetController());
	controller->PlayRumbleFeedBack(.75f, 1, true, true, true, true);
	
	
	if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_LivingRoomEvent0))
	{
		FTimerDelegate OnTimerCompleted;

		OnTimerCompleted.BindLambda([&]
		{
			for (auto Element : Lights_AllLights)
			{
				if(Element->GetLightZone() != HouseZone::LivingRoom) continue;
				Element->TurnOff();
			}
	
			for (auto Element : Skeletals_LivingRoomEvet)
			{
				Element->Destroy();
			}

			UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyNearEvent);
			
			if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_LivingRoomEvent1))
			{
				FTimerDelegate OnSecondTimerCompleted;
				OnSecondTimerCompleted.BindLambda([&]
				{
					for (auto Element : Lights_AllLights)
					{
						if(Element->GetLightZone() != HouseZone::LivingRoom) continue;
						Element->TurnOn();
					}
				});
				
			GetWorld()->GetTimerManager().SetTimer(Timer_LivingRoomEvent1, OnSecondTimerCompleted, 1.5f, false);
			}
		});
		
		GetWorld()->GetTimerManager().SetTimer(Timer_LivingRoomEvent0, OnTimerCompleted, 0.9f, false);
	}
	
	TriggerVolume_LivingRoomEvent->Destroy();
}

void AGameFlowDiaryLevelOtherWorld::OnTriggerKitchenEventOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || bKitchenEventDone) return;

	bKitchenEventDone = true;
	
	for (auto Element : Lights_AllLights)
	{
		if(Element->GetLightZone() != HouseZone::Kitchen) continue;
		Element->TurnOff();
	}
	
	for (auto Element : Skeletals_KitchenEvet)
	{
		Element->Destroy();
	}
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyNearEvent);

	auto controller = Cast<AAlexPlayerController>(Player->GetController());
	controller->PlayRumbleFeedBack(.4f, .75, false, true, false, true);
	
	
	if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_KitchenEvent))
	{
		FTimerDelegate OnTimerCompleted;

		OnTimerCompleted.BindLambda([&]
		{
			for (auto Element : Lights_AllLights)
			{
				if(Element->GetLightZone() != HouseZone::Kitchen) continue;
				Element->TurnOn();
			}
		});
		GetWorld()->GetTimerManager().SetTimer(Timer_KitchenEvent, OnTimerCompleted, 1.5f, false);
	}
	
	TriggerVolume_KitchenEvent->Destroy();
}

void AGameFlowDiaryLevelOtherWorld::OnTriggerDinningRoomEventOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || !bEventReadyDinningRoom || bDinningRoomEventDone) return;

	bDinningRoomEventDone = true;

	auto controller = Cast<AAlexPlayerController>(Player->GetController());
	controller->PlayRumbleFeedBack(.7f, 1, true, false, true, false);
	
	for (auto Element : Lights_DinningEventLights)
	{
		Element->Destroy();
	}
	
	for (auto Element : Skeletals_DinningRoomEvet)
	{
		Element->Destroy();
	}
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyNearEvent);
	
	if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_DinningRoomEvent))
	{
		FTimerDelegate OnTimerCompleted;

		OnTimerCompleted.BindLambda([&]
		{
			for (auto Element : Lights_AllLights)
			{
				if(Element->GetLightZone() != HouseZone::DiningRoom) continue;
				Element->TurnOn();
			}
		});
		
		GetWorld()->GetTimerManager().SetTimer(Timer_DinningRoomEvent, OnTimerCompleted, 1.5f, false);
	}

	TriggerVolume_DinningEvent->Destroy();
}

void AGameFlowDiaryLevelOtherWorld::OnTriggerEndGamePassOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || bEndGamePassDone) return;
	bEndGamePassDone = true;

	auto controller = Cast<AAlexPlayerController>(Player->GetController());
	controller->PlayRumbleFeedBack(1, 5, true, true, true, true);
	
	Doors_EndGame->HardClosing();
	Doors_EndGame->SetLockedState(true);

	TriggerVolume_EndGamePass->Destroy();
}