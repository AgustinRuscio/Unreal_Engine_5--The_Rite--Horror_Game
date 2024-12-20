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
#include "TheRite/AmbientObjects/Manikin.h"
#include "Sound/AmbientSound.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "Engine/StaticMeshActor.h"
#include "TheRite/Characters/Alex.h"
#include "HideAndSeekPuzzle.h"
#include "BasePlayerSettingsSetter.h"
#include "Engine/TargetPoint.h"
#include "TheRite/AmbientObjects/Candle.h"
#include "Engine/SpotLight.h"
#include "Components/AudioComponent.h"
#include "Engine/BlockingVolume.h"
#include "Misc/TextFilterExpressionEvaluator.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AGameFlowPacifierLevel::AGameFlowPacifierLevel()
{
	PrimaryActorTick.bCanEverTick = true;
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::BeginPlay()
{
	Super::BeginPlay();
	
	LightSwitch_ThermalSwitch->OnInteractionTrigger.AddDynamic(this, &AGameFlowPacifierLevel::OnLightsOnEvent);
	
	if(GameFlow_HideAndSeekPuzzle->IsActive())
	{
		GameFlow_HideAndSeekPuzzle->OnPuzzleComplete.AddDynamic(this, &AGameFlowPacifierLevel::EndGame);
		GameFlow_HideAndSeekPuzzle->OnPuzzleStarted.AddDynamic(this, &AGameFlowPacifierLevel::OnHideSeekPuzzleStarted);

		for (auto Element : Meshes_HideSeekObjects)
		{
			Element->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
			Element->GetStaticMeshComponent()->SetVisibility(false);
		}
	}
	
	InteractorForManiquiesToAppear->OnInteractionTrigger.AddDynamic(this, &AGameFlowPacifierLevel::PlaceMannequinsInCorridor);
	AtticLadder->OnInteractionTrigger.AddDynamic(this, &AGameFlowPacifierLevel::PlaceMannequinsStairs);
	Interactable_BedroomLightsOn->OnInteractionTrigger.AddDynamic(this, &AGameFlowPacifierLevel::LightsOnBedRoom);
	
	AtticLadder->DisableLadder();

	for (auto Element : Candles_EndGame)
	{
		Element->Disappear();
	}
	
	InitializeValues();
	BindColliderMethods();
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Timer_LastPuzzleStarted.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Initialization Methods
void AGameFlowPacifierLevel::BindColliderMethods()
{
	TriggerVolume_LightsOut->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerLightsOutEventOverlap);
	TriggerVolume_EndGmaePass->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerEndGamePassOverlap);
	
	TriggerVolume_TiffanyStairsEvent->OnActorBeginOverlap.AddDynamic(this, &AGameFlowPacifierLevel::OnTriggerStairsTiffanyEventOverlap);
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::InitializeValues()
{
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
	BlockingVolumeOriginalLocation = BlockingVolume->GetActorLocation();
	
	AudioComponent_Ambient->GetAudioComponent()->Sound = SFX_Ambient;
	AudioComponent_StressSound->GetAudioComponent()->Sound = SFX_StressSound;
	AudioComponent_Voices->GetAudioComponent()->Sound = SFX_Voices;

	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OnLastPuzzleTimerTick"));
	Timer_LastPuzzleStarted.AddInterpFloat(CurveFloat_LastPuzzle, TimelineCallback);
	
	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("OnLasPuzzleTimerFinished"));
	Timer_LastPuzzleStarted.SetTimelineFinishedFunc(TimelineFinishedCallback);
	
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region Blocking volume Methods
void AGameFlowPacifierLevel::PlaceBlockingVolume(FVector NewLocation, FRotator NewRotation = FRotator::ZeroRotator)
{
	BlockingVolume->SetActorLocation(NewLocation,false, nullptr, ETeleportType::TeleportPhysics);

	if(NewRotation != FRotator::ZeroRotator)
		BlockingVolume->SetActorRotation(NewRotation);
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::ResetBlockingVolumePosition()
{
	BlockingVolume->SetActorLocation(BlockingVolumeOriginalLocation,false,
		nullptr, ETeleportType::TeleportPhysics);
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region Audio Methods
void AGameFlowPacifierLevel::RaiseAmbientVolume(float newVolumeMultiplier)
{
	AudioComponent_Ambient->GetAudioComponent()->VolumeMultiplier = newVolumeMultiplier;
	AudioComponent_StressSound->GetAudioComponent()->VolumeMultiplier = newVolumeMultiplier;
	AudioComponent_Voices->GetAudioComponent()->VolumeMultiplier = newVolumeMultiplier;
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::ResetAmbientVolume()
{
	AudioComponent_Ambient->GetAudioComponent()->VolumeMultiplier = 1;
	AudioComponent_StressSound->GetAudioComponent()->VolumeMultiplier = 1;
	AudioComponent_Voices->GetAudioComponent()->VolumeMultiplier = 1;
}
#pragma endregion 

//----------------------------------------------------------------------------------------------------------------------
#pragma region Event Methods
void AGameFlowPacifierLevel::PlaceMannequinsInCorridor(AInteractor* Interactor)
{
	int8 count = 0;

	for (auto Element : A_CorridorMannequins)
	{
		Element->SetActorLocation(TargetPoint_CorridorManiquiesPosition[count]->GetActorLocation());
		Element->SetActorRotation(TargetPoint_CorridorManiquiesPosition[count]->GetActorRotation());
		Element->Activate();
		
		count++;
	}
	
	UGameplayStatics::SpawnSound2D(GetWorld(),SFX_TiffanyBreath);
	UGameplayStatics::SpawnSound2D(GetWorld(),SFX_TiffanyNear);
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::PlaceMannequinsStairs(AInteractor* Interactor)
{
	if(!bLightsRestored) return;

	for (auto Element : Actors_StairsMannequins)
	{
		Element->GetStaticMeshComponent()->SetVisibility(true);
		Element->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	}
	
	AtticLadder->OnInteractionTrigger.RemoveDynamic(this, &AGameFlowPacifierLevel::PlaceMannequinsStairs);
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::OnLightsOnEvent(AInteractor* Interactor)
{
	bLightsRestored = true;
	int8 count = 0;
	
	for (auto Element : Actors_ScaryMannequins)
	{
		Element->SetActorLocation(TargetPoint_ScaryManiquiesPosition[count]->GetActorLocation());
		Element->SetActorRotation(TargetPoint_ScaryManiquiesPosition[count]->GetActorRotation());
		count++;
	}

	count = 0;
	for (auto Element : Actors_NormalMannequins)
	{
		Element->SetActorLocation(TargetPoint_NormalManiquiesNewPosition[count]->GetActorLocation());
		Element->SetActorRotation(TargetPoint_NormalManiquiesNewPosition[count]->GetActorRotation());
		count++;
	}

	for (auto Element : EmergencyLights)
	{
		Element->TurnOff();
	}

	auto controller = Cast<AAlexPlayerController>(Player->GetController());
	controller->PlayRumbleFeedBack(.85, .2, true, true, true, true);
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_PowerRestored);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyNear);
	Door_BedRoom->SetLockedState(false);
	//Door_BedRoom->Open();
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::LightsOnBedRoom(AInteractor* Interactor)
{
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyNear);
	
	for (auto Element : Lights_AllLights)
	{
		if(Element->GetLightZone() != HouseZone::BedRoom) continue;

		Element->TurnOn();
	}

	MainFetus->StartAudioComponent();
	Interactable_BedroomLightsOn->OnInteractionTrigger.RemoveDynamic(this, &AGameFlowPacifierLevel::LightsOnBedRoom);
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::OnHideSeekPuzzleStarted()
{
	for (auto Element : Meshes_HideSeekObjects)
	{
		Element->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
		Element->GetStaticMeshComponent()->SetVisibility(true);
	}

	for (auto Element : Lights_AllLights)
	{
		Element->ChangeLightIntensity((Element->GetIntensity() - 10), true);
	}
	
	//Timer_LastPuzzleStarted.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::EndGame()
{	
	for (auto Element : Candles_EndGame)
	{
		Element->Appear();
		Element->TurnOn();
	}

	Door_EndGmae->SetLockedState(false);

	Player->SetPlayerOptions(true, true, false);
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_EndGame);
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::OnLastPuzzleTimerTick(float deltaSeconds)
{
	RaiseAmbientVolume(deltaSeconds);
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("X %f"), deltaSeconds));
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::OnLasPuzzleTimerFinished() { }

//----------------------------------------------------------------------------------------------------------------------
#pragma region Collision Methods
void AGameFlowPacifierLevel::OnTriggerLightsOutEventOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || bLightsOutEventDone) return;
	bLightsOutEventDone = true;
	
	AtticLadder->EnableLadder();
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

//----------------------------------------------------------------------------------------------------------------------
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
		
			for (auto Element : EmergencyLights)
			{
				Element->TurnOn();
			}
			
			ResetAmbientVolume();
			ResetBlockingVolumePosition();
			Skeletal_TiffanyStairs->Destroy();
		});

		GetWorld()->GetTimerManager().SetTimer(Timer_FirstStairsEvent, FirstTimerDelegate,2, false);
	}
	
	TriggerVolume_TiffanyStairsEvent->Destroy();
}

//----------------------------------------------------------------------------------------------------------------------
void AGameFlowPacifierLevel::OnTriggerEndGamePassOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || bEndGamePassDone) return;
	bEndGamePassDone = true;
	
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(1, 5, true, true, true, true);
	
	TriggerVolume_EndGmaePass->Destroy();
}
#pragma endregion