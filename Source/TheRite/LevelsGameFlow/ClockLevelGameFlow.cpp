//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ClockLevelGameFlow.h"
#include "CloclLevelArtRoomEvent.h"
#include "Components/AudioComponent.h"
#include "Engine/TargetPoint.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/MinutesLetter.h"
#include "TheRite/Interactuables/BigClock.h"
#include "TheRite/Interactuables/HourLetter.h"
#include "TheRite/Interactuables/DoorKey.h"
#include "MoveTiffany.h"
#include "TheRite/Interactuables/RecordPlayer.h"
#include "Engine/StaticMeshActor.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Engine/TriggerVolume.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "Engine/TriggerBox.h"
#include "Engine/BlockingVolume.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Characters/Tiffany.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Containers/Map.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/AmbientObjects/Candle.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/AmbientObjects/Candle.h"


AClockLevelGameFlow::AClockLevelGameFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//---------------- System Class Methods
void AClockLevelGameFlow::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));
	//Player->SetPlayerOptions(false, true);

	for (auto Element : Walls_EndGameWall)
	{
		Element->GetStaticMeshComponent()->SetVisibility(false);
		Element->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}

	for (auto Element : Candles_EndGame)
	{
		Element->Disappear();
	}

	Actor_EndGamePassWall->GetStaticMeshComponent()->SetVisibility(false);
	Actor_EndGamePassWall->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	//SetTutorialUI();
	
	BindTimeLineMethods();
	
	SetAudioSettings();
	
	BindPuzzleEvents();
	BindEvents();
}

void AClockLevelGameFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	JumpscareSecondTimeLine.TickTimeline(DeltaTime);
	
	MakeTiffanyTalk(DeltaTime);
	MakeBreath(DeltaTime);
}

void AClockLevelGameFlow::HideTutorialWidget()
{
	TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
}

//---------------- Initialize Methods
void AClockLevelGameFlow::SetAudioSettings()
{
	AmbientMusicCompoenent = UGameplayStatics::SpawnSound2D(GetWorld(), AmbientMusic);
	StressSoundMusicCompoenent = UGameplayStatics::SpawnSound2D(GetWorld(), StressSound);
	VoicesSoundMusicCompoenent = UGameplayStatics::SpawnSound2D(GetWorld(), VoicesSound);

	AmbientMusicOriginalVolumen = AmbientMusic->GetVolumeMultiplier();
	StressSoundOriginalVolumen = StressSound->GetVolumeMultiplier();
	VoicesSoundOriginalVolumen = VoicesSound->GetVolumeMultiplier();
}

void AClockLevelGameFlow::BindPuzzleEvents()
{
	MinutesLetter->OnAction.AddDynamic(this, &AClockLevelGameFlow::GetMinutes);
	HoursLetter->OnAction.AddDynamic(this, &AClockLevelGameFlow::GetHours);

	
	ArtRoomEvent->OnArtRoomEventStarted.AddDynamic(this, &AClockLevelGameFlow::VoicesSoundIncrease);
	ArtRoomEvent->OnArtRoomEventFinished.AddDynamic(this, &AClockLevelGameFlow::VoicesSoundSetOrigialVolumen);

	LibraryTriggerVolumenFirst->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapFirstLibraryTriggerBegin);
	LibraryTriggerVolumenJumpScared->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginJumpscare);
	LibraryTriggerVolumenJumpScaredReady->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginJumpscareReady);
}

void AClockLevelGameFlow::BindEvents()
{
	LibraryKey->OnKeyCollected.AddDynamic(this, &AClockLevelGameFlow::SpawnTiffanyForLibraryKeyCollected);
	LibraryKey->OnKeyCollected.AddDynamic(this, &AClockLevelGameFlow::OnLibraryKeyCollected);
	
	HallKeyEventMoveTiffanyTrigger->OnFinishedEvent.AddDynamic(this, &AClockLevelGameFlow::OnWalkFinished);
	BigLockedDoor->OnInteractionTrigger.AddDynamic(this, &AClockLevelGameFlow::OnInteractionWithLockedDoor);
	
	Trigger_LockEndGameDoors->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginLockDoorsEndGame);
	KnockTrigger->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginKnock);
	CloseGaregeDoorTriggerVolumen->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginCloseGarageDoor);

	TriggerVolume_EndGamePass->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnTriggerEndGamePassOverlap);

	
	BigClock->OnClockPuzzleCompleted.AddDynamic(this, &AClockLevelGameFlow::EndGame);
}

void AClockLevelGameFlow::SetTutorialUI()
{
	TutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), TutorialUI);
	TutorialWidget->AddToViewport();
	TutorialWidget->SetVisibility(ESlateVisibility::Hidden);

	auto alexController = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	
	if(alexController)
		alexController->OnKeyPressed.AddDynamic(TutorialWidget, &UTutorialWidget::SetKeyMode);
	
	TutorialWidget->SetVisibility(ESlateVisibility::Visible);
		
	if (!GetWorldTimerManager().IsTimerActive(TutorialTimerHandle))
	{
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([&]
		{
			TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
		});
		
		//GetWorldTimerManager().SetTimer(TutorialTimerHandle, timerDelegate, 6.f, false);
		GetWorldTimerManager().SetTimer(TutorialTimerHandle, this, &AClockLevelGameFlow::HideTutorialWidget, 4.f, false);
	}
}

//---------------- Tick Methods
void AClockLevelGameFlow::MakeTiffanyTalk(float time)
{
	if(TiffanyTalkTimer > TiffanyTalkCD)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), TiffanyTalkCue);
		TiffanyTalkCD = FMath::RandRange(60.0f, 120.0f);
		TiffanyTalkTimer = 0;
	}
	else
		TiffanyTalkTimer += time;
}

void AClockLevelGameFlow::MakeBreath(float time)
{
	if(BreathTimer > BreathCD)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), TiffanyBreathkCue);
		BreathCD = FMath::RandRange(25.0f, 190.0f);
		BreathTimer = 0;
	}
	else
		BreathTimer += time;
}

//---------------- Letters Methods
void AClockLevelGameFlow::GetMinutes()
{
	MinutesCollected();
	bLibraryPuzzleStarted = true;
	bMinutes = true;

	CheckLetters();
}

void AClockLevelGameFlow::GetHours()
{
	bHours = true;
	
	CheckLetters();
}

void AClockLevelGameFlow::CheckLetters()
{
	if(!bHours || !bMinutes) return;

	for (auto Element : Walls_EndGameWall)
	{
		Element->GetStaticMeshComponent()->SetVisibility(true);
		Element->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndProbe);
	}

	for (auto Element : Candles_EndGame)
	{
		Element->Appear();
		Element->TurnOn();
	}
	
	BigClock->SetReadyToUse();
}

void AClockLevelGameFlow::MinutesCollected()
{
	LibraryDoor->SetLockedState(true);
	bMinutes = true;
	LibraryRoofLight->TurnOff();
	
	RecordPlayer->PlaySong();
	RecordPlayer->OnSongPaused.AddDynamic(this, &AClockLevelGameFlow::OnSoundPaused);

	PlaceBlockingVolumen(BlockingVolumenLibraryPosition->GetActorLocation(), FRotator::ZeroRotator);

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_LightSwitch);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyHeavyBreath);
	UGameplayStatics::SpawnSound2D(GetWorld(), TiffanyTalkCue);
}

void AClockLevelGameFlow::LockDoorsEndGame()
{
	LibraryDoor->SetLockedState(true);
	ArtRoomDoor->SetLockedState(true);
	
	VoicesSoundMusicCompoenent->SetVolumeMultiplier(VoicesSoundMusicCompoenent->VolumeMultiplier * 5);
	AmbientMusicCompoenent->SetVolumeMultiplier(AmbientMusicCompoenent->VolumeMultiplier * 2);
	StressSoundMusicCompoenent->SetVolumeMultiplier(StressSoundMusicCompoenent->VolumeMultiplier * 2);
	
	LibraryDoor->HardClosing();
	ArtRoomDoor->HardClosing();

	auto controller = Cast<AAlexPlayerController>(Player->GetController());
	controller->PlayRumbleFeedBack(.85, .2, true, true, true, true);
	
	Trigger_LockEndGameDoors->Destroy();
}

void AClockLevelGameFlow::EndGame()
{
	for (auto Element : Lights)
	{
		Element->TurnOff();
		UGameplayStatics::SpawnSound2D(GetWorld(), SFX_LightsBroken);
	}

	for (auto Element : ActorTobeDestroyOnEndgame)
	{
		Element->Destroy();
	}
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_LastAudio);
	
	Player->ForceTalk(OhFuckAlexTalk);
	Player->ForceTurnLighterOn();
	
	Player->SetPlayerOptions(true, false, false);
}

//---------------- Audio Methods
void AClockLevelGameFlow::VoicesSoundSetOrigialVolumen()
{
	VoicesSoundMusicCompoenent->SetVolumeMultiplier(VoicesSoundOriginalVolumen);
}

void AClockLevelGameFlow::VoicesSoundIncrease()
{
	VoicesSoundMusicCompoenent->SetVolumeMultiplier(VoicesSoundMusicCompoenent->VolumeMultiplier * 20);
}

void AClockLevelGameFlow::OnSoundPaused()
{
	HitCounterLibrary = 1;
}

//---------------- Blocking volumen Methods
void AClockLevelGameFlow::PlaceBlockingVolumen(FVector NewLocation, FRotator NewRotation = FRotator::ZeroRotator)
{
	BlockingVolume->SetActorLocation(NewLocation,false, nullptr, ETeleportType::TeleportPhysics);

	if(NewRotation != FRotator::ZeroRotator)
		BlockingVolume->SetActorRotation(NewRotation);
}

void AClockLevelGameFlow::ResetBlockingVolumenPosition()
{
	BlockingVolume->SetActorLocation(BlockingVolumeOriginalLocation->GetActorLocation(),false,
		nullptr, ETeleportType::TeleportPhysics);
}

//---------------- Spawn Methods
void AClockLevelGameFlow::SpawnPlanksOnDoor()
{
	for (auto Element : PlanksToBeSpawnOnTiffanyWalk)
	{
		Element->FindComponentByClass<UStaticMeshComponent>()->SetVisibility(true);
	}
}

void AClockLevelGameFlow::SpawnTiffanyForLibraryKeyCollected()
{
	FVector const& position = HallKeyEventTiffanySpawnPoint->GetActorLocation();
	FRotator const& rotation = HallKeyEventTiffanySpawnPoint->GetActorRotation();
	
	ATiffany* tiff = GetWorld()->SpawnActor<ATiffany>(TiffanyClassForSpawning, position, rotation);

	HallKeyEventMoveTiffanyTrigger->AsignTiffany(tiff);
}

//---------------- Interaction Methods
void AClockLevelGameFlow::OnLibraryKeyCollected()
{
	PlaceBlockingVolumen(BlockingVolumeLibraryEntrancePosition->GetActorLocation(), FRotator::ZeroRotator);
}

void AClockLevelGameFlow::OnWalkFinished()
{
	ResetBlockingVolumenPosition();
}

void AClockLevelGameFlow::OnInteractionWithLockedDoor(AInteractor* Interactor)
{
	Player->ForceTalk(SFX_BigDoor);
}

void AClockLevelGameFlow::OnJumpscareFinished()
{
	ResetBlockingVolumenPosition();
	
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_TiffanyLaugh);
	
	LibraryDoor->SetLockedState(false);

	for (auto Element : LibraryLightsEvent)
	{
		Element->TurnOn();
	}
	
	LibraryRoofLight->TurnOn();
	
	Player->OnJumpscaredFinished.RemoveDynamic(this, &AClockLevelGameFlow::OnJumpscareFinished);
}

//---------------- TimeLine Methods
void AClockLevelGameFlow::BindTimeLineMethods()
{
	FOnTimelineFloat SecondJumpscareTimelineCallback;
	SecondJumpscareTimelineCallback.BindUFunction(this, FName("FirstTimeLineUpdate"));
	JumpscareSecondTimeLine.AddInterpFloat(JumpscareSecondTimeLineCurve, SecondJumpscareTimelineCallback);
	
	FOnTimelineEventStatic SecondJumpscareTimeLineCallbackFinished;
	SecondJumpscareTimeLineCallbackFinished.BindUFunction(this, FName("OnSecondJumpscareTimelineFinished"));
	JumpscareSecondTimeLine.SetTimelineFinishedFunc(SecondJumpscareTimeLineCallbackFinished);
}

void AClockLevelGameFlow::OnSecondJumpscareTimelineFinished()
{
	LibraryTriggerVolumenFirst->Destroy();
	LibraryTriggerVolumenJumpScared->Destroy();

	ResetBlockingVolumenPosition();

	for (auto Element : LibraryLightsEvent)
	{
		Element->TurnOn();
	}
	
	Player->OnJumpscaredFinished.RemoveDynamic(this, &AClockLevelGameFlow::OnJumpscareFinished);
}

//---------------- Bind Colliders Methods
void AClockLevelGameFlow::OnOverlapFirstLibraryTriggerBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;

	if(!bLibraryPuzzleStarted) return;
	
	if(HitCounterLibrary == 0)
	{
		Player->ForceTalk(SFX_Alex_IHateThatSong);
	}
	else
	{
		if(!DoOnceLibrary == 0) return;

		DoOnceLibrary++;
		
		LibraryRoofLight->TurnOn();
		LibraryTiffany->GetMesh()->SetVisibility(true, false);
		
		UGameplayStatics::SpawnSound2D(GetWorld(), TiffanyTalkCue);
		UGameplayStatics::SpawnSound2D(GetWorld(), DropSound);
		
		bLibraryJumpScaredReady = true;
		RecordPlayer->PlaySong();

		Player->ForceTalk(SFX_Alex_WhatwasThat);
		
		auto controller = Cast<AAlexPlayerController>(Player->GetController());
		controller->PlayRumbleFeedBack(.1f, 5, false, true, false, true);
	}
}

void AClockLevelGameFlow::OnOverlapBeginJumpscare(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || !bLibraryJumpScaredReady || DoOnceJumpscare > 0) return;
	
	DoOnceJumpscare++;
	
	Player->ForceLighterOff();
	Player->SetPlayerOptions(false, false, true);
	
	for (auto Element : LibraryLightsEvent)
	{
		Element->TurnOff();
	}
	
	LibraryRoofLight->TurnOff();

	RecordPlayer->PauseSong();

	
	if(!GetWorldTimerManager().IsTimerActive(JumpscareHandleSecond))
	{
		FTimerDelegate timerDelegate;
		
		timerDelegate.BindLambda([&]
		{
			LibraryTiffany->Destroy();
			
			auto controller = Cast<AAlexPlayerController>(Player->GetController());
			controller->PlayRumbleFeedBack(.5f, .3, true, true, true, true);
			
			if(!GetWorldTimerManager().IsTimerActive(JumpscareHandleFirst))
			{
				FTimerDelegate timerDelegate;
		
				timerDelegate.BindLambda([&]
				{
					for (auto Element : LibraryLightsEvent)
					{
						Element->TurnOn();
					}
			
						LibraryRoofLight->TurnOn();
						Player->ForceTalk(AudioIShouldGetOutOfHere);
						Player->SetPlayerOptions(false, true, true);
						OnJumpscareFinished();
						LibraryTriggerVolumenJumpScaredReady->Destroy();
				});
		
				GetWorldTimerManager().SetTimer(JumpscareHandleFirst,timerDelegate, 3.f, false);
			}
		});
		
		GetWorldTimerManager().SetTimer(JumpscareHandleSecond,timerDelegate, 1.f, false);
	}
	
}

void AClockLevelGameFlow::OnOverlapBeginJumpscareReady(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || !IShouldGetOutOfHere || DoOnceJumpscareReady > 0) return;

	DoOnceJumpscareReady++;

	for (auto Element : LibraryLightsEvent)
	{
		Element->TurnOff();
	}
	
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyScream);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Heartbeat);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyNear);

	Player->OnJumpscaredFinished.AddDynamic(this, &AClockLevelGameFlow::OnJumpscareFinished);
	
	Player->OnJumpScare();
}

void AClockLevelGameFlow::OnOverlapBeginLockDoorsEndGame(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || !bMinutes || !bHours) return;

	LockDoorsEndGame();
}

void AClockLevelGameFlow::OnOverlapBeginKnock(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor))return;

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Knocking);
	KnockTrigger->Destroy();
}

void AClockLevelGameFlow::OnOverlapBeginCloseGarageDoor(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;

	auto controller = Cast<AAlexPlayerController>(Player->GetController());
	controller->PlayRumbleFeedBack(.2f, .3, true, true, true, true);
	
	GarageDoor->SetLockedState(true);
	GarageDoor->HardClosing();
	CloseGaregeDoorTriggerVolumen->Destroy();
}

void AClockLevelGameFlow::OnTriggerEndGamePassOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || bEndGamePassDone) return;
	bEndGamePassDone = true;

	auto controller = Cast<AAlexPlayerController>(Player->GetController());
	controller->PlayRumbleFeedBack(1, 5, true, true, true, true);
	
	Actor_EndGamePassWall->GetStaticMeshComponent()->SetVisibility(true);
	Actor_EndGamePassWall->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	TriggerVolume_EndGamePass->Destroy();
}
