#include "ClockLevelGameFlow.h"

#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Tiffany.h"
#include "Containers/Map.h"
#include "TheRite/Interactuables/DoorKey.h"


AClockLevelGameFlow::AClockLevelGameFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AClockLevelGameFlow::SetVariables()
{
	Player = Cast<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(),AAlex::StaticClass()));

	Player->GetHint()->SetChildActorClass(AHandLetter::StaticClass());
	//PlayerHint = Cast<AHandLetter>(Player->GetHint());
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
	HintUIOn();
	//PlayerHint->SetOfficeMaterial();
	bHours = true;
	OnPartOfClockGain.Broadcast();
}

void AClockLevelGameFlow::FirstLetterRead()
{
	GarageDoor->SetLockedState(false);
	Player->SetHintState(true);
	HintUIOn();
}

void AClockLevelGameFlow::HintUIOn()
{
	HintsWidget->MakeVisible();
}

void AClockLevelGameFlow::MinutesCollected()
{
	LibraryDoor->SetLockedState(true);
	bMinutes = true;
	LibraryRoofLight->TurnOff();
	
	RecordPlayer->PlaySong();
	RecordPlayer->OnSongPaused.AddDynamic(this, &AClockLevelGameFlow::OnSoundPaused);

	PlaceBlockingVolumen(BlockingVolumenLibraryPosition->GetActorLocation());

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyHeavyBreath);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyTalkingToAlex);
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
		
		UGameplayStatics::SpawnSound2D(GetWorld(), SFX_TiffanyTalkingToAlex);
		
		bLibraryJumpScaredReady = true;
		RecordPlayer->PlaySong();

		Player->ForceTalk(SFX_Alex_GoingInside);
		Player->CameraTargeting(RecordPlayer->GetActorLocation());
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
	
	Player->OnJumpScare();

	JumpscareFirstTimeLine.PlayFromStart();
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
	Player->SetCanUseLigherState(true);
	
	EndGameTriggerVolumen->Destroy();
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
	UE_LOG(LogTemp, Warning, TEXT("Finished"));
	LibraryTriggerVolumenFirst->Destroy();
	LibraryTriggerVolumenJumpScared->Destroy();

	ResetBlockingVolumenPosition();

	for (auto Element : LibraryLightsEvent)
	{
		Element->TurnOn();
	}

	LibraryDoor->SetLockedState(false);
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_TiffanyLaugh);
}

void AClockLevelGameFlow::SetDrawers()
{
	//for (auto Element : Drawers)
	//{
	//	Element->OnDrawerOpen.AddDynamic(this, &AClockLevelGameFlow::DrawerPuzzle);
	//}

	for (auto Element : Map_Drawers_Target)
	{
		Element.Key->OnDrawerOpen.AddDynamic(this, &AClockLevelGameFlow::DrawerPuzzle);
		UE_LOG(LogTemp, Warning, TEXT("a"));
		UE_LOG(LogTemp, Warning, TEXT("drawer name %s"), *Element.Key->GetName());
	}

	
	//for (int32 Index = 0; Index < Drawers.Num(); ++Index)
	//{
	//	ABaseDrawer* CurrentDrawer = Drawers[Index];
	//	ATargetPoint* CurrentTargetPoint = DrawersTargetsPoint[Index];
	//	
	//	Map_Drawers_Target.Add(CurrentDrawer, CurrentTargetPoint);
	//}
}

void AClockLevelGameFlow::DrawerPuzzle(ABaseDrawer* Drawer)
{
	if(!bOnDrawerPuzzle) return;

	if(DrawersOpened < MinDrawerOpenedUntilscreams)
	{
		++DrawersOpened;

		if(DrawersOpened == 1) return;
		
		if(DrawersOpened == 2)
			Player->ForceTalk(SFX_WhereDidILeftTheKey);
		else
			Player->ForceTalk(SFX_WhereIsTheDeamKey);
	}
	else
	{
		if(Drawer->IsKeyContainer())
		{
			bOnDrawerPuzzle = false;
			Player->ForceTalk(SFX_ImLoosingMyMind);
		}
		else
		{
			Drawer->AddingForce();
			Player->ForceTalk(SFX_AlexScream);
		}

		if(DoOnceDrawers > 0) return;

		int RandomDrawer = FMath::RandRange(0,Map_Drawers_Target.Num()-1);

		TArray<TPair<ABaseDrawer*, ATargetPoint*>> Pairs;
		
		for (const TPair<ABaseDrawer*, ATargetPoint*>& Pair : Map_Drawers_Target)
		{
			Pairs.Add(Pair);
		}

		SpawnArtRoomKey(Pairs[RandomDrawer].Value, Pairs[RandomDrawer].Key);
	}
}

void AClockLevelGameFlow::SpawnArtRoomKey(ATargetPoint* SpawnPoint, ABaseDrawer* ParentDrawer)
{
	if(DoOnceSpawnKey > 0) return;
	++DoOnceSpawnKey;

	ParentDrawer->SetKeyContainer();

	FVector const& Position = SpawnPoint->GetActorLocation();
	FRotator const& Rotation = SpawnPoint->GetActorRotation();
	
	ADoorKey* DrawerKey = GetWorld()->SpawnActor<ADoorKey>(KeySubclass, Position, Rotation);
	DrawerKey->SetZone("Art Room");
	DrawerKey->SetDoor(ArtRoomDoor);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld, true);
	
	DrawerKey->AttachToActor(ParentDrawer,AttachmentRules);

	DrawerKey->OnKeyCollected.AddDynamic(this, &AClockLevelGameFlow::OnDrawerKeyCollected);
}

void AClockLevelGameFlow::OnDrawerKeyCollected()
{
	for (auto Element : Lights)
	{
		Element->AggresiveMatterial();
	}

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Steps);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_HeavyBreath);

	
	UE_LOG(LogTemp, Error, TEXT("Drawer Start"));
	DrawerTimeline.Play();
}

void AClockLevelGameFlow::OnDrawerTimelineFinished()
{
	for (auto Element : Lights)
	{
		Element->NormalMatterial();
	}
	UE_LOG(LogTemp, Error, TEXT("Drawer Ready"));
}


void AClockLevelGameFlow::SetHintsWidget()
{
	HintsWidget = CreateWidget<UHintsWidget>(GetWorld(), HintsUI);
	HintsWidget->AddToViewport();
	HintsWidget->SetVisibility(ESlateVisibility::Hidden);
}


void AClockLevelGameFlow::BeginPlay()
{
	Super::BeginPlay();
	BindTimLinemethods();
	
	UGameplayStatics::SpawnSound2D(GetWorld(), AmbientMusic);
	UGameplayStatics::SpawnSound2D(GetWorld(), RainEffect);

	SetHintsWidget();
	SetVariables();
	BindPuzzleEvents();
	
	MaxPortraitsDown = FMath::RandRange(4, Portraits.Num() / 3);

	SetDrawers();
	
	LibraryKey->OnKeyCollected.AddDynamic(this, &AClockLevelGameFlow::SpawnTiffanyForLibraryKeyCollected);
	LibraryKey->OnKeyCollected.AddDynamic(this, &AClockLevelGameFlow::OnLibraryKeyCollected);
	
	MakeTiffanyWalk->OnFinished.AddDynamic(this, &AClockLevelGameFlow::OnWalkFinished);
	BigLockedDoor->OnInteraction.AddDynamic(this, &AClockLevelGameFlow::OnInteractionWithLockedDoor);

	LibraryTriggerVolumenFirst->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapFirstLibraryTriggerBegin);
	LibraryTriggerVolumenJumpScared->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginJumpscare);
	
	EndGameTriggerVolumen->OnActorBeginOverlap.AddDynamic(this, &AClockLevelGameFlow::OnOverlapBeginEndGame);
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
	PlaceBlockingVolumen(BlockingVolumeEntrancePosition->GetActorLocation());
}

void AClockLevelGameFlow::OnWalkFinished()
{
	ResetBlockingVolumenPosition();
}

void AClockLevelGameFlow::OnInteractionWithLockedDoor()
{
	Player->ForceTalk(SFX_BigDoor);
}

void AClockLevelGameFlow::PlaceBlockingVolumen(FVector NewLocation)
{
	BlockingVolume->SetActorLocation(NewLocation,false, nullptr, ETeleportType::TeleportPhysics);
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
	}
	else
		TiffanyTalkTimer += time;
}

auto AClockLevelGameFlow::MakeBreath(float time) -> void
{
	if(BreathTimer > BreathCD)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BreathkCue);
		BreathCD = FMath::RandRange(25.0f, 190.0f);
	}
	else
	{
		BreathTimer += time;
	}
}

void AClockLevelGameFlow::DropPortrait(float DeltaTime)
{
	if(!bCanDrop) return;
	if(MaxPortraitsDown > PortraitsDown) return;
	
	if(PortraitTimer < PortraitDownCD)
		PortraitTimer += DeltaTime;
	else
	{
		for (auto Element : Portraits)
		{
			UStaticMeshComponent* MeshComponent = Element->GetStaticMeshComponent();
			
			if (!MeshComponent || !MeshComponent->WasRecentlyRendered()) continue;
			
			MeshComponent->SetSimulatePhysics(true);

			MeshComponent->SetEnableGravity(true); 
			MeshComponent->SetLinearDamping(0.2f);

			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PortraitDropedCue, MeshComponent->GetComponentLocation());
			Portraits.Remove(Element);
			++PortraitsDown;
			PortraitTimer = 0.0f;
			
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindLambda([=]()
			{
				MeshComponent->SetSimulatePhysics(false);
				PortraitTimerHandle.Invalidate();
			});

			GetWorldTimerManager().SetTimer(PortraitTimerHandle, TimerDelegate, 2.0f, false);
			return;
		}
	}
}

void AClockLevelGameFlow::BindTimLinemethods()
{
	//------Drawers
	FOnTimelineFloat DrawerKeyObteinTimelineCallback;
	DrawerKeyObteinTimelineCallback.BindUFunction(this, FName("FirstTimeLineUpdate"));
	DrawerTimeline.AddInterpFloat(DrawerTimeLineCurve, DrawerKeyObteinTimelineCallback);
	
	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("OnDrawerTimelineFinished"));
	DrawerTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);

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
	
	DrawerTimeline.TickTimeline(DeltaTime);
	JumpscareFirstTimeLine.TickTimeline(DeltaTime);
	JumpscareSecondTimeLine.TickTimeline(DeltaTime);
	

	MakeTiffanyTalk(DeltaTime);
	MakeBreath(DeltaTime);

	DropPortrait(DeltaTime);
}
