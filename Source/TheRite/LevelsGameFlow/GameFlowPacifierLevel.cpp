//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "GameFlowPacifierLevel.h"
#include "TheRite/Interactuables/LightSwitch.h"
#include "Engine/TriggerVolume.h"
#include "TheRite/AmbientObjects/EmergencyLights.h"
#include "TheRite/Interactuables/Ladder.h"
#include "TheRite/Interactuables/Door.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "Animation/SkeletalMeshActor.h"
#include "Sound/AmbientSound.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Characters/Alex.h"
#include "BasePlayerSettingsSetter.h"
#include "Engine/TargetPoint.h"
#include "TheRite/AmbientObjects/Candle.h"
#include "FetusPuzzle.h"
#include "Components/AudioComponent.h"
#include "Engine/BlockingVolume.h"

AGameFlowPacifierLevel::AGameFlowPacifierLevel()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameFlowPacifierLevel::BeginPlay()
{
	Super::BeginPlay();

	LightSwitch_TermicalSwitch->OnInteractionTrigger.AddDynamic(this, &AGameFlowPacifierLevel::OnLightsOnEvent);
	GameFlow_FetusPuzzle->OnPuzzleComplete.AddDynamic(this, &AGameFlowPacifierLevel::EndGame);
	
	AtticLader->DisableLadder();

	InitializeValues();
	BindColliderMethods();
}

void AGameFlowPacifierLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameFlowPacifierLevel::BindColliderMethods()
{
	TriggerVolume_LightsOut->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerLightsOutEventOverlap);
	TriggerVolume_EndGmaePass->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerEndGamePassOverlap);

	
	TriggerVolume_LucyRoom->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerLucyRoomOverlap);
	TriggerVolume_LucyRoom->OnActorEndOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerLucyRoomOverlapEnd);
	
	TriggerVolume_TiffanyBedRoom->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerDestroyTiffanyBedRoomOverlap);
	TriggerVolume_TiffanyStairsEvent->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerStairsTiffanyEventOverlap);
}

void AGameFlowPacifierLevel::InitializeValues()
{
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
	BlockingVolumeOriginalLocation = BlockingVolume->GetActorLocation();
	
	AudioComponent_Ambient->GetAudioComponent()->Sound = SFX_Ambient;
	AudioComponent_StressSound->GetAudioComponent()->Sound = SFX_StressSound;
	AudioComponent_Voices->GetAudioComponent()->Sound = SFX_Voices;
}

void AGameFlowPacifierLevel::OnLightsOnEvent(AInteractor* Interactor)
{
	for (auto Element : EmergencyLights)
	{
		Element->TurnOff();
	}

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_PowerRestored);
	Door_BedRoom->SetLockedState(false);
	Door_BedRoom->Open();
}

//---------------- Blocking volume Methods
void AGameFlowPacifierLevel::PlaceBlockingVolume(FVector NewLocation, FRotator NewRotation = FRotator::ZeroRotator)
{
	BlockingVolume->SetActorLocation(NewLocation,false, nullptr, ETeleportType::TeleportPhysics);

	if(NewRotation != FRotator::ZeroRotator)
		BlockingVolume->SetActorRotation(NewRotation);
}

void AGameFlowPacifierLevel::ResetBlockingVolumePosition()
{
	BlockingVolume->SetActorLocation(BlockingVolumeOriginalLocation,false,
		nullptr, ETeleportType::TeleportPhysics);
}

void AGameFlowPacifierLevel::RaiseAmbientVolume(float newVolumeMultiplier)
{
	AudioComponent_Ambient->GetAudioComponent()->VolumeMultiplier = newVolumeMultiplier;
	AudioComponent_StressSound->GetAudioComponent()->VolumeMultiplier = newVolumeMultiplier;
	AudioComponent_Voices->GetAudioComponent()->VolumeMultiplier = newVolumeMultiplier;
}

void AGameFlowPacifierLevel::ResetAmbientVolume()
{
	AudioComponent_Ambient->GetAudioComponent()->VolumeMultiplier = 1;
	AudioComponent_StressSound->GetAudioComponent()->VolumeMultiplier = 1;
	AudioComponent_Voices->GetAudioComponent()->VolumeMultiplier = 1;
}

void AGameFlowPacifierLevel::EndGame()
{
	for (auto Element : Candles_EndGame)
	{
		Element->TurnOn();
	}
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_EndGame);
	Door_EndGame->SetLockedState(false);
}

void AGameFlowPacifierLevel::OnTriggerLightsOutEventOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || bLightsOutEventDone) return;
	bLightsOutEventDone = true;

	AtticLader->EnableLadder();
	Door_BathRoomRoom->SetLockedState(false);
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_LightsOut);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_PowerDowns);

	Skeletal_TiffanyStairs->GetSkeletalMeshComponent()->SetVisibility(true);
	PlaceBlockingVolume(TargetPoint_CorridorBlockingVolumeLocation->GetActorLocation());
	bLightsDown = true;
	
	for (auto Element : Lights_AllLights)
	{
		Element->TurnOff();
	}

	 for (auto Element : EmergencyLights)
	 {
	 	Element->TurnOn();
	 }

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(.15f, 3, true, true, true, true);
	
	TriggerVolume_LightsOut->Destroy();
}

void AGameFlowPacifierLevel::OnTriggerStairsTiffanyEventOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || !bLightsDown) return;

	for (auto Element : EmergencyLights)
	{
		Element->TurnOff();
	}
	
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(1, 5, true, true, true, true);

	RaiseAmbientVolume(10);
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyNear);
	
	if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_FirstStairsEvent))
	{
		FTimerDelegate FirstTimerDelegate;
		FirstTimerDelegate.BindLambda([&]
		{
			
			Skeletal_TiffanyStairs->SetActorLocation(TargetPoint_TiffanyStairClosePosition->GetActorLocation());
			
			for (auto Element : EmergencyLights)
			{
				Element->TurnOn();
			}
			
			if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_SecondEvent))
			{
				FTimerDelegate SecondTimerDelegate;
				SecondTimerDelegate.BindLambda([&]
				{
					for (auto Element : EmergencyLights)
					{
						Element->TurnOff();
					}

					Skeletal_TiffanyStairs->Destroy();

					if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_ThirdEvent))
					{
						FTimerDelegate ThirdTimerDelegate;
						ThirdTimerDelegate.BindLambda([&]
						{
							for (auto Element : EmergencyLights)
							{
								Element->TurnOn();
							}

							ResetBlockingVolumePosition();
							ResetAmbientVolume();
							
						});

						GetWorld()->GetTimerManager().SetTimer(Timer_ThirdEvent, ThirdTimerDelegate,2.f, false);
					}
				});

				GetWorld()->GetTimerManager().SetTimer(Timer_SecondEvent, SecondTimerDelegate,.75f, false);
			}
			
		});

		GetWorld()->GetTimerManager().SetTimer(Timer_FirstStairsEvent, FirstTimerDelegate,2, false);
	}
}

void AGameFlowPacifierLevel::OnTriggerDestroyTiffanyBedRoomOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;
	
	for (auto Element : Lights_AllLights)
	{
		if(Element->GetLightZone() != HouseZone::BedRoom) continue;
		Element->TurnOff();
	}

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyNear);
	
	if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_BedRoomEvent))
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([&]
		{
			Skeletal_TiffanyBedRoom->Destroy();
			
			for (auto Element : Lights_AllLights)
			{
				if(Element->GetLightZone() != HouseZone::BedRoom) continue;
				Element->TurnOn();
			}
		});

		GetWorld()->GetTimerManager().SetTimer(Timer_BedRoomEvent, TimerDelegate,5, false);
	}
}

void AGameFlowPacifierLevel::OnTriggerLucyRoomOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;
	
	PlayerSettingsSetter->SetUseLighter(false);
	Player->ForceLighterOff();
}

void AGameFlowPacifierLevel::OnTriggerLucyRoomOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;
	
	PlayerSettingsSetter->SetUseLighter(true);
}

void AGameFlowPacifierLevel::OnTriggerEndGamePassOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || bEndGamePassDone) return;
	bEndGamePassDone = true;
	
	Door_EndGame->HardClosing();
	
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(1, 5, true, true, true, true);
	
	TriggerVolume_EndGmaePass->Destroy();
}