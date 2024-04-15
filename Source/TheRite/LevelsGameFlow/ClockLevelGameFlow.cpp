//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ClockLevelGameFlow.h"

#include "Components/AudioComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TheRite/Characters/Tiffany.h"
#include "Containers/Map.h"
#include "TheRite/Interactuables/DoorKey.h"


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
	OnPartOfClockGain.AddDynamic(this, &AClockLevelGameFlow::CheckInteraction);

	GarageDoor->SetLockedState(true);
	
	TiffanyFirstLetter->OnAction.AddDynamic(this, &AClockLevelGameFlow::FirstLetterRead);
	
	MinutesLetter->OnAction.AddDynamic(this, &AClockLevelGameFlow::GetMinutes);

	HoursLetter->OnAction.AddDynamic(this, &AClockLevelGameFlow::GetHours);
	
}
void AClockLevelGameFlow::CheckInteraction()
{
	if(bMinutes && bHours) return;
	if(!bMinutes && ! bHours) return;


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



void AClockLevelGameFlow::GetMinutes()
{
	MinutesCollected();
	bLibraryPuzzleStarted = true;
	bMinutes = true;
	OnPartOfClockGain.Broadcast();
}

void AClockLevelGameFlow::GetHours()
{
	//HintUIOn();
	//PlayerHint->SetOfficeMaterial();
	bHours = true;
	OnPartOfClockGain.Broadcast();
}

void AClockLevelGameFlow::FirstLetterRead()
{
	GarageDoor->SetLockedState(false);
	Player->SetHintState(true);
	//HintUIOn();
}

//void AClockLevelGameFlow::HintUIOn()
//{
//	HintsWidget->MakeVisible();
//}

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
		Player->CameraTargeting(RecordPlayer->GetActorLocation());
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

void AClockLevelGameFlow::OnOverlapBeginJumpscare(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || !bLibraryJumpScaredReady || DoOnceJumpscare > 0) return;
	
	DoOnceJumpscare++;
	
	LibraryTiffany->Destroy();
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyScream);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Heartbeat);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyNear);

	Player->OnJumpscaredFinished.AddDynamic(this, &AClockLevelGameFlow::OnJumpscareFinished);
	
	Player->OnJumpScare();

	JumpscareFirstTimeLine.PlayFromStart();
}

void AClockLevelGameFlow::OnJumpscareFinished()
{
	LibraryRoofLight->TurnOff();
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

	LibraryDoor->SetLockedState(false);
	
	Player->OnJumpscaredFinished.RemoveDynamic(this, &AClockLevelGameFlow::OnJumpscareFinished);
	
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_TiffanyLaugh);
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

	Player->SetPlayerStats(false, true);

	
	ArtRoomEvent->OnArtRoomEventStarted.AddDynamic(this, &AClockLevelGameFlow::VoicesSoundIncrease);
	ArtRoomEvent->OnArtRoomEventFinished.AddDynamic(this, &AClockLevelGameFlow::VoicesSoundSetOrigialVolumen);
	
	LibraryKey->OnKeyCollected.AddDynamic(this, &AClockLevelGameFlow::SpawnTiffanyForLibraryKeyCollected);
	LibraryKey->OnKeyCollected.AddDynamic(this, &AClockLevelGameFlow::OnLibraryKeyCollected);
	
	MakeTiffanyWalk->OnFinishedEvent.AddDynamic(this, &AClockLevelGameFlow::OnWalkFinished);
	BigLockedDoor->OnInteraction.AddDynamic(this, &AClockLevelGameFlow::OnInteractionWithLockedDoor);

	LibraryTriggerVolumenFirst->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapFirstLibraryTriggerBegin);
	LibraryTriggerVolumenJumpScared->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginJumpscare);
	
	EndGameTriggerVolumen->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginEndGame);
	KnockTrigger->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginKnock);
	CloseGaregeDoorTriggerVolumen->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginCloseGarageDoor);
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

	MakeTiffanyWalk->KeyObtein(tiff);
	tiff->SetHasToMove(true);

	TArray<ATargetPoint*> tiffWaypoints;
	tiffWaypoints.Add(TiffanySpawnPoint);
	
	tiff->SetWaypoints(tiffWaypoints);
}

void AClockLevelGameFlow::OnLibraryKeyCollected()
{
	PlaceBlockingVolumen(BlockingVolumeEntrancePosition->GetActorLocation(), FRotator::ZeroRotator);
}

void AClockLevelGameFlow::OnWalkFinished()
{
	ResetBlockingVolumenPosition();
}

void AClockLevelGameFlow::OnInteractionWithLockedDoor()
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
	//------First Library
	FOnTimelineFloat FirstJumpscareTimelineCallback;
	FirstJumpscareTimelineCallback.BindUFunction(this, FName("FirstTimeLineUpdate"));
	JumpscareFirstTimeLine.AddInterpFloat(JumpscareFirstTimeLineCurve, FirstJumpscareTimelineCallback);
	
	FOnTimelineEventStatic FirstJumpscareTimeLineCallbackFinished;
	FirstJumpscareTimeLineCallbackFinished.BindUFunction(this, FName("OnFirstJumpscareTimelineFinished"));
	JumpscareFirstTimeLine.SetTimelineFinishedFunc(FirstJumpscareTimeLineCallbackFinished);
	
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
	
	JumpscareFirstTimeLine.TickTimeline(DeltaTime);
	JumpscareSecondTimeLine.TickTimeline(DeltaTime);
	
	MakeTiffanyTalk(DeltaTime);
	MakeBreath(DeltaTime);
}