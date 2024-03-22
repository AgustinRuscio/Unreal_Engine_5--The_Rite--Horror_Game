#include "ClockLevelDrawersPuzzle.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"

AClockLevelDrawersPuzzle::AClockLevelDrawersPuzzle()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AClockLevelDrawersPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	GetPlayer();
	BindTimeLine();
	SetDrawers();
}

void AClockLevelDrawersPuzzle::BindTimeLine()
{
	FOnTimelineFloat DrawerKeyObteinTimelineCallback;
	DrawerKeyObteinTimelineCallback.BindUFunction(this, FName("FirstTimeLineUpdate"));
	DrawerTimeline.AddInterpFloat(DrawerTimeLineCurve, DrawerKeyObteinTimelineCallback);
	
	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("OnDrawerTimelineFinished"));
	DrawerTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
}

void AClockLevelDrawersPuzzle::GetPlayer()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		APawn* ControlledPawn = PlayerController->GetPawn();

		if (ControlledPawn)
			Player = Cast<AAlex>(ControlledPawn);
	}
}

void AClockLevelDrawersPuzzle::ResolveSpawnKey()
{
	DoOnceDrawers++;
	
	TArray<TPair<ABaseDrawer*, ATargetPoint*>> Pairs;
		
	for (const TPair<ABaseDrawer*, ATargetPoint*>& Pair : Map_Drawers_Target)
	{
		if(Pair.Key->IsOpen()) continue;
			
		Pairs.Add(Pair);
	}
	int RandomDrawer = FMath::RandRange(0,Pairs.Num()-1);
	
	SpawnArtRoomKey(Pairs[RandomDrawer].Value, Pairs[RandomDrawer].Key);
}

void AClockLevelDrawersPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawerTimeline.TickTimeline(DeltaTime);
}

void AClockLevelDrawersPuzzle::SetDrawers()
{
	for (auto Element : Map_Drawers_Target)
	{
		Element.Key->OnDrawerOpen.AddDynamic(this, &AClockLevelDrawersPuzzle::DrawerPuzzle);
	}
}


void AClockLevelDrawersPuzzle::DrawerPuzzle(ABaseDrawer* Drawer)
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
		if(DoOnceDrawers == 0)
		{
			ResolveSpawnKey();
		}
		else
		{
			if(Drawer->IsKeyContainer())
			{
				bOnDrawerPuzzle = false;
				Player->ForceTalk(SFX_ImLoosingMyMind);
				
				FMovieSceneSequencePlaybackSettings PlaybackSettings;
				PlaybackSettings.PlayRate = 1.0f; 
				PlaybackSettings.bAutoPlay = true;
				PlaybackSettings.bRandomStartTime = false;
				
				ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	
				ULevelSequencePlayer* sequencePlayer =  ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceFade,
																							PlaybackSettings,TempLevelSequenceActor);


				Player->ForceDisableInput();
				sequencePlayer->OnFinished.AddDynamic(Player, &AAlex::ForceEnableInput);
				
				sequencePlayer->Play();
				Destroy();
			}
			else
			{
				Drawer->AddingForce();

				if(!bScreamFlipFlop)
				{
					bScreamFlipFlop = true;
					return;
				}
				
				bScreamFlipFlop = false;
				Player->ForceTalk(SFX_AlexScream);
			}
		}
	}
}


void AClockLevelDrawersPuzzle::SpawnArtRoomKey(ATargetPoint* SpawnPoint, ABaseDrawer* ParentDrawer)
{
	if(DoOnceSpawnKey > 0) return;
	++DoOnceSpawnKey;

	ParentDrawer->SetKeyContainer();

	FVector const& Position = SpawnPoint->GetActorLocation();
	FRotator const& Rotation = SpawnPoint->GetActorRotation();
	
	ADoorKey* DrawerKey = GetWorld()->SpawnActor<ADoorKey>(KeySubclass, Position, Rotation);
	DrawerKey->SetDoor(ArtRoomDoor);
	DrawerKey->SetPickeableSettings(true, "Art room key", PickableItemsID::ArtRoomKey);
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld, true);
	
	DrawerKey->AttachToActor(ParentDrawer,AttachmentRules);

	DrawerKey->OnKeyCollected.AddDynamic(this, &AClockLevelDrawersPuzzle::OnDrawerKeyCollected);
}

void AClockLevelDrawersPuzzle::OnDrawerKeyCollected()
{
	for (auto Element : Lights)
	{
		Element->AggresiveMatterial();
	}

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Steps);
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_HeavyBreath);
	
	DrawerTimeline.Play();
}

void AClockLevelDrawersPuzzle::OnDrawerTimelineFinished()
{
	for (auto Element : Lights)
	{
		Element->NormalMatterial();
	}
}
