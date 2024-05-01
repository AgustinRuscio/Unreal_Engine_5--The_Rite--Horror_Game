//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ClockLevelGameFlow.h"
#include "CloclLevelArtRoomEvent.h"
#include "Components/AudioComponent.h"
#include "Engine/TargetPoint.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/MinutesLetter.h"
#include "TheRite/Interactuables/HourLetter.h"
#include "TheRite/Interactuables/DoorKey.h"
#include "MoveTiffany.h"
#include "TheRite/Interactuables/RecordPlayer.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/TriggerBox.h"
#include "Engine/BlockingVolume.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Characters/Tiffany.h"
#include "TheRite/Triggers/MakeTiffanyWalk.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Containers/Map.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Interactuables/Letter.h"


AClockLevelGameFlow::AClockLevelGameFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AClockLevelGameFlow::SetVariables()
{
	Player = Cast<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));
}

void AClockLevelGameFlow::BindPuzzleEvents()
{
	GarageDoor->SetLockedState(true);
	
	TiffanyFirstLetter->OnAction.AddDynamic(this, &AClockLevelGameFlow::FirstLetterRead);
	
	MinutesLetter->OnAction.AddDynamic(this, &AClockLevelGameFlow::GetMinutes);

	HoursLetter->OnAction.AddDynamic(this, &AClockLevelGameFlow::GetHours);
	
}
void AClockLevelGameFlow::CheckInteraction() { }

void AClockLevelGameFlow::GetMinutes()
{
	MinutesCollected();
	bLibraryPuzzleStarted = true;
	bMinutes = true;
}

void AClockLevelGameFlow::GetHours()
{
	bHours = true;
}

void AClockLevelGameFlow::FirstLetterRead()
{
	GarageDoor->SetLockedState(false);
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

void AClockLevelGameFlow::OnSoundPaused()
{
	HitCounterLibrary = 1;
}

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
	}
}


//--------- JUMPSCARE
void AClockLevelGameFlow::OnOverlapBeginJumpscare(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || !bLibraryJumpScaredReady || DoOnceJumpscare > 0) return;
	
	DoOnceJumpscare++;
	
	Player->ForceLighterOff();
	Player->SetPlayerOptions(false, false);
	
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
						Player->SetPlayerOptions(false, true);
						IShouldGetOutOfHere = true;
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

void AClockLevelGameFlow::OnFirstJumpscareTimelineFinished()
{
	for (auto Element : LibraryLightsEvent)
	{
		Element->TurnOff();
	}

	JumpscareSecondTimeLine.PlayFromStart();
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

void AClockLevelGameFlow::OnOverlapBeginEndGame(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || !bMinutes || !bHours)return;

	LibraryDoor->SetLockedState(true);
	ArtRoomDoor->SetLockedState(true);
	LibraryDoor->HardClosing();
	ArtRoomDoor->HardClosing();

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
	
	Player->SetPlayerOptions(true, false);
	
	EndGameTriggerVolumen->Destroy();
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

	GarageDoor->SetLockedState(true);
	GarageDoor->HardClosing();
	CloseGaregeDoorTriggerVolumen->Destroy();
}

void AClockLevelGameFlow::OnDrawerTimelineFinished()
{
	for (auto Element : Lights)
	{
		Element->NormalMatterial();
	}
}


void AClockLevelGameFlow::BeginPlay()
{
	Super::BeginPlay();
	BindTimLinemethods();
	
	AmbientMusicCompoenent = UGameplayStatics::SpawnSound2D(GetWorld(), AmbientMusic);
	StressSoundMusicCompoenent = UGameplayStatics::SpawnSound2D(GetWorld(), StressSound);
	VoicesSoundMusicCompoenent = UGameplayStatics::SpawnSound2D(GetWorld(), VoicesSound);

	AmbientMusicOriginalVolumen = AmbientMusic->GetVolumeMultiplier();
	StressSoundOriginalVolumen = StressSound->GetVolumeMultiplier();
	VoicesSoundOriginalVolumen = VoicesSound->GetVolumeMultiplier();
	
	SetVariables();
	BindPuzzleEvents();

	Player->SetPlayerOptions(false, true);

	
	ArtRoomEvent->OnArtRoomEventStarted.AddDynamic(this, &AClockLevelGameFlow::VoicesSoundIncrease);
	ArtRoomEvent->OnArtRoomEventFinished.AddDynamic(this, &AClockLevelGameFlow::VoicesSoundSetOrigialVolumen);
	
	LibraryKey->OnKeyCollected.AddDynamic(this, &AClockLevelGameFlow::SpawnTiffanyForLibraryKeyCollected);
	LibraryKey->OnKeyCollected.AddDynamic(this, &AClockLevelGameFlow::OnLibraryKeyCollected);
	
	MakeTiffanyWalk->OnFinishedEvent.AddDynamic(this, &AClockLevelGameFlow::OnWalkFinished);
	BigLockedDoor->OnInteractionTrigger.AddDynamic(this, &AClockLevelGameFlow::OnInteractionWithLockedDoor);

	LibraryTriggerVolumenFirst->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapFirstLibraryTriggerBegin);
	LibraryTriggerVolumenJumpScared->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginJumpscare);
	LibraryTriggerVolumenJumpScaredReady->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginJumpscareReady);
	
	EndGameTriggerVolumen->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginEndGame);
	KnockTrigger->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginKnock);
	CloseGaregeDoorTriggerVolumen->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginCloseGarageDoor);



	TArray<ATargetPoint*> Waypoints;
	Waypoints.Add(TiffanySpawnPointOneItem);
	
	FVector const& position =TiffanySpawnPointOneItem->GetActorLocation();
	FRotator const& rotation =TiffanySpawnPointOneItem->GetActorRotation();
	
	auto tiff =GetWorld()->SpawnActor<ATiffany>(MidTiff, position, rotation);

	
	tiff->SetActorLocation(position);
	tiff->SetActorRotation(rotation);
	
	MakeTiffanyWalkBetweenDoors->KeyObtein(tiff);
	MakeTiffanyWalkBetweenDoors->OnStartEvent.AddDynamic(this, &AClockLevelGameFlow::VoicesSoundIncrease);
	MakeTiffanyWalkBetweenDoors->OnFinishedEvent.AddDynamic(this, &AClockLevelGameFlow::VoicesSoundSetOrigialVolumen);
	MakeTiffanyWalkBetweenDoors->OnFinishedEvent.AddDynamic(this, &AClockLevelGameFlow::SpawnPlanksOnDoor);
	
	tiff->SetWaypoints(Waypoints);
	tiff->SetHasToMove(true);

}

void AClockLevelGameFlow::VoicesSoundIncrease()
{
	VoicesSoundMusicCompoenent->SetVolumeMultiplier(VoicesSoundMusicCompoenent->VolumeMultiplier * 20);
}

void AClockLevelGameFlow::SpawnPlanksOnDoor()
{
	for (auto Element : PlanksToBeSpawnOnTiffanyWalk)
	{
		Element->FindComponentByClass<UStaticMeshComponent>()->SetVisibility(true);
	}
}

void AClockLevelGameFlow::VoicesSoundSetOrigialVolumen()
{
	VoicesSoundMusicCompoenent->SetVolumeMultiplier(VoicesSoundOriginalVolumen);
}

void AClockLevelGameFlow::SpawnTiffanyForLibraryKeyCollected()
{
	FVector const& position = TiffanySpawnPoint->GetActorLocation();
	FRotator const& rotation = TiffanySpawnPoint->GetActorRotation();
	
	ATiffany* tiff = GetWorld()->SpawnActor<ATiffany>(MidTiff, position, rotation);

	MakeTiffanyWalk->AsignTiffany(tiff);
	//tiff->SetHasToMove(false);

	//TArray<ATargetPoint*> tiffWaypoints;
	//tiffWaypoints.Add(TiffanySpawnPoint);
	//
	//tiff->SetWaypoints(tiffWaypoints);
}

void AClockLevelGameFlow::OnLibraryKeyCollected()
{
	PlaceBlockingVolumen(BlockingVolumeEntrancePosition->GetActorLocation(), FRotator::ZeroRotator);
}

void AClockLevelGameFlow::OnWalkFinished()
{
	ResetBlockingVolumenPosition();
}

void AClockLevelGameFlow::OnInteractionWithLockedDoor(AInteractor* Interactor)
{
	Player->ForceTalk(SFX_BigDoor);
}

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

auto AClockLevelGameFlow::MakeBreath(float time) -> void
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


void AClockLevelGameFlow::BindTimLinemethods()
{
	//------Seconds Library
	FOnTimelineFloat SecondJumpscareTimelineCallback;
	SecondJumpscareTimelineCallback.BindUFunction(this, FName("FirstTimeLineUpdate"));
	JumpscareSecondTimeLine.AddInterpFloat(JumpscareSecondTimeLineCurve, SecondJumpscareTimelineCallback);
	
	FOnTimelineEventStatic SecondJumpscareTimeLineCallbackFinished;
	SecondJumpscareTimeLineCallbackFinished.BindUFunction(this, FName("OnSecondJumpscareTimelineFinished"));
	JumpscareSecondTimeLine.SetTimelineFinishedFunc(SecondJumpscareTimeLineCallbackFinished);
}


void AClockLevelGameFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	JumpscareSecondTimeLine.TickTimeline(DeltaTime);
	
	MakeTiffanyTalk(DeltaTime);
	MakeBreath(DeltaTime);
}