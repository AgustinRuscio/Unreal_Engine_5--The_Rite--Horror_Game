#include "RedDoor.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"

ARedDoor::ARedDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CreateEditorComponents();
}

void ARedDoor::BindTimeLines()
{
	FOnTimelineFloat LatchAnimTimelineCallback;
	LatchAnimTimelineCallback.BindUFunction(this, FName("LatchAnimTimeLineUpdate"));
	TimeLineLatchAnim.AddInterpFloat(ItsLockedCurve, LatchAnimTimelineCallback);
	
	FOnTimelineFloat OpenTimelineCallback;
	OpenTimelineCallback.BindUFunction(this, FName("OpenTimeLineUpdate"));
	TimeLineOpenDoor.AddInterpFloat(CurveOpenDoor, OpenTimelineCallback);
	
	FOnTimelineEventStatic OpenTimelineFinishedCallback;
	OpenTimelineFinishedCallback.BindUFunction(this, FName("OpenTimelineFinished"));
	TimeLineOpenDoor.SetTimelineFinishedFunc(OpenTimelineFinishedCallback);


	FOnTimelineEventStatic FadeFinishedCallback;
	FadeFinishedCallback.BindUFunction(this, FName("FadeTimelineFinished"));
	FadeTimeLine.SetTimelineFinishedFunc(FadeFinishedCallback);
}

void ARedDoor::CreateEditorComponents()
{
	DoorItself = CreateDefaultSubobject<UStaticMeshComponent>("Door Itself");
	
	USceneComponent* NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NewRootComponent"));
	SetRootComponent(NewRootComponent);

	DoorItself->SetupAttachment(NewRootComponent);
	
	DoorItself->SetMobility(EComponentMobility::Movable);
	
	BaseFront = CreateDefaultSubobject<UStaticMeshComponent>("Front base");
	BaseBack = CreateDefaultSubobject<UStaticMeshComponent>("Back base");
	BaseBack->SetMobility(EComponentMobility::Movable);
	BaseFront->SetMobility(EComponentMobility::Movable);

	LatchFront = CreateDefaultSubobject<USkeletalMeshComponent>("Front Latch");
	LatchBack = CreateDefaultSubobject<USkeletalMeshComponent>("Back Latch");
	LatchFront->SetMobility(EComponentMobility::Movable);
	LatchBack->SetMobility(EComponentMobility::Movable);

	EmmisivePlane = CreateDefaultSubobject<UStaticMeshComponent>("Emmisive Plane");
	EmmisivePlane->SetupAttachment(NewRootComponent);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	
	BaseFront->SetupAttachment(DoorItself);
	BaseBack->SetupAttachment(DoorItself);
	LatchFront->SetupAttachment(DoorItself);
	LatchBack ->SetupAttachment(DoorItself);
	BoxCollision->SetupAttachment(DoorItself);
}

void ARedDoor::OpenTimeLineUpdate(float value)
{
	float Yaw = FMath::Lerp(0,90, value);
	
	DoorItself->SetRelativeRotation(FRotator(0,Yaw,0));
}

void ARedDoor::OpenTimelineFinished()
{
	UGameplayStatics::SpawnSound2D(GetWorld(), SFXRedDoor);
	FadeTimeLine.Play();
}

void ARedDoor::FadeTimelineFinished()
{
	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.PlayRate = 1.0f; 
	PlaybackSettings.bAutoPlay = true;
	PlaybackSettings.bRandomStartTime = false;
	
	ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	
	ULevelSequencePlayer* player =  ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceFade,
																				PlaybackSettings,TempLevelSequenceActor);

	player->OnFinished.AddDynamic(this, &ARedDoor::ChangeLevel);
	
	player->Play();
}

void ARedDoor::LatchAnimTimeLineUpdate(float value)
{
	float lerpValue = FMath::Lerp(5, 50, value);
	LatchFront->SetRelativeRotation(FRotator(lerpValue, 0, 0));
	LatchBack->SetRelativeRotation(FRotator(lerpValue, 0, -180));
}

void ARedDoor::ChangeLevel()
{
	UGameplayStatics::OpenLevel(this, NextLevelName);
}

void ARedDoor::BeginPlay()
{
	Super::BeginPlay();
	BindTimeLines();
}

void ARedDoor::Interaction()
{
	if(bAlreadyOpen) return;

	bAlreadyOpen = true;
	GetWorld()->GetFirstPlayerController()->GetPawn()->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	TimeLineLatchAnim.PlayFromStart();
	UGameplayStatics::PlaySound2D(GetWorld(), SFXDoor);

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->DisableInput(controller);
	
	TimeLineOpenDoor.Play();
}

void ARedDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeLineOpenDoor.TickTimeline(DeltaTime);
	FadeTimeLine.TickTimeline(DeltaTime);
	TimeLineLatchAnim.TickTimeline(DeltaTime);
}