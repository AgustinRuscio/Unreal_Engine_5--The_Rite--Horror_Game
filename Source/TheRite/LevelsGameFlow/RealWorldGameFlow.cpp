#include "RealWorldGameFlow.h"

#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"


ARealWorldGameFlow::ARealWorldGameFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ARealWorldGameFlow::CreateWidgets()
{
	FirstTutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), FirstTutorialMenu);
	FirstTutorialWidget->AddToViewport(0);
	FirstTutorialWidget->SetVisibility(ESlateVisibility::Hidden);
	FirstTutorialWidget->SetIsFocusable(true);

	SecondTutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), SecondsTutorialMenu);
	SecondTutorialWidget->AddToViewport(0);
	SecondTutorialWidget->SetVisibility(ESlateVisibility::Hidden);
	SecondTutorialWidget->SetIsFocusable(true);

	auto controller = GetWorld()->GetFirstPlayerController();
	
	if(auto alexController = Cast<AAlexPlayerController>(controller))
	{
		alexController->OnKeyPressed.AddDynamic(SecondTutorialWidget, &UTutorialWidget::SetKeyMode);
		alexController->OnKeyPressed.AddDynamic(FirstTutorialWidget, &UTutorialWidget::SetKeyMode);
	}
	
}

void ARealWorldGameFlow::OpenArtRoomDoor()
{
	if(bCloseDoor) return;
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_DoorOpening);
	Player->ForceTalk(ReactToLockedDoorAudio);
	
	ArtRoomDoor->Open();
	bCloseDoor = true;
	
	for (auto const Element : ArtRoomRedLights)
	{
		Element->SpotLightComponent->SetIntensity(1000.0f);
	}
}

void ARealWorldGameFlow::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor) || !bCloseDoor || DoOnce > 0) return;

	++DoOnce;
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_SlamDoor);
	ArtRoomDoor->HardClosing();
	
	OnCloseTimeline.Play();
}



void ARealWorldGameFlow::BindTimeLine()
{
	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("OnCloseTimeLineFinished"));
	OnCloseTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
}


void ARealWorldGameFlow::OnCloseTimeLineFinished()
{
	ArtRoomTiffany->Destroy();

	for (auto const Element : ArtRoomRedLights)
	{
		Element->Destroy();
	}

	ArtRoomDoor->SetLockedState(false);
	SlamDoorTriggerVolume->Destroy();
}
void ARealWorldGameFlow::GetPlayer()
{
	auto const tempSearch = UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass());
	Player = CastChecked<AAlex>(tempSearch);
}

void ARealWorldGameFlow::OnOverlapBeginKnock(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor))return;

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Knocking);
	KnockTrigger->Destroy();
}



void ARealWorldGameFlow::BeginPlay()
{
	Super::BeginPlay();

	CreateWidgets();
	
	SlamDoorTriggerVolume->OnActorBeginOverlap.AddDynamic(this, &ARealWorldGameFlow::OnOverlapBegin);
	
	BindTimeLine();
	GetPlayer();
	
	Player->ForceTalk(FirstTalkAudio);
	KnockTrigger->OnActorBeginOverlap.AddDynamic(this, &ARealWorldGameFlow::OnOverlapBeginKnock);
	
	LockedInteractionDoor->OnInteraction.AddDynamic(this, &ARealWorldGameFlow::OpenArtRoomDoor);

	if (!GetWorldTimerManager().IsTimerActive(ShowFirstTutorialWidget))
		GetWorldTimerManager().SetTimer(ShowFirstTutorialWidget, this, &ARealWorldGameFlow::ShowingFirstTutorialWidget, 3.0f, false);
}

void ARealWorldGameFlow::ShowingFirstTutorialWidget()
{
	FirstTutorialWidget->SetVisibility(ESlateVisibility::Visible);
	
	if (!GetWorldTimerManager().IsTimerActive(HideFirstTutorialWidget))
		GetWorldTimerManager().SetTimer(HideFirstTutorialWidget, this, &ARealWorldGameFlow::HidingFirstTutorialWidget, 3.0f, false);
}

void ARealWorldGameFlow::HidingFirstTutorialWidget()
{
	FirstTutorialWidget->SetVisibility(ESlateVisibility::Hidden);
	if (!GetWorldTimerManager().IsTimerActive(ShowSecondTutorialWidget))
		GetWorldTimerManager().SetTimer(ShowSecondTutorialWidget, this, &ARealWorldGameFlow::ShowingSecondTutorialWidget, 3.0f, false);
}

void ARealWorldGameFlow::ShowingSecondTutorialWidget()
{
	SecondTutorialWidget->SetVisibility(ESlateVisibility::Visible);
	
	if (!GetWorldTimerManager().IsTimerActive(HideSecondTutorialWidget))
		GetWorldTimerManager().SetTimer(HideSecondTutorialWidget, this, &ARealWorldGameFlow::HidingSecondTutorialWidget, 3.0f, false);
}

void ARealWorldGameFlow::HidingSecondTutorialWidget()
{
	SecondTutorialWidget->SetVisibility(ESlateVisibility::Hidden);
}
	
void ARealWorldGameFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnCloseTimeline.TickTimeline(DeltaTime);
}