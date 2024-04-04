//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "CloclLevelArtRoomEvent.h"

#include "Components/AudioComponent.h"
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"

ACloclLevelArtRoomEvent::ACloclLevelArtRoomEvent()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ACloclLevelArtRoomEvent::BindTimeLines()
{
	StartTriggerBox->OnActorBeginOverlap.AddDynamic(this, &ACloclLevelArtRoomEvent::OnEventStarted);
	
	
	//----- During First Lights Out
	FOnTimelineFloat FirstTurnOffCallbackUpdate;
	FirstTurnOffCallbackUpdate.BindUFunction(this, FName("DuringFirstTurnOffTick"));
	FirstTurnOffTimeLine.AddInterpFloat(TurnOffCurve, FirstTurnOffCallbackUpdate);
	
	FOnTimelineEventStatic FirstTurnOffCallbackFinished;
	FirstTurnOffCallbackFinished.BindUFunction(this, FName("FirstTurnOffFinished"));
	FirstTurnOffTimeLine.SetTimelineFinishedFunc(FirstTurnOffCallbackFinished);

	//----- First Lights On
	FOnTimelineFloat FirstTurnOnCallbackUpdate;
	FirstTurnOnCallbackUpdate.BindUFunction(this, FName("DuringFirstTurnOnTick"));
	FirstTurnOnTimeLine.AddInterpFloat(TurnOnCurve, FirstTurnOnCallbackUpdate);
	
	FOnTimelineEventStatic FirstTurnOnCallbackFinished;
	FirstTurnOnCallbackFinished.BindUFunction(this, FName("OnFirstTurnOnFinished"));
	FirstTurnOnTimeLine.SetTimelineFinishedFunc(FirstTurnOnCallbackFinished);

	//----- During Second Lights Out
	FOnTimelineFloat SecondTurnOffCallbackUpdate;
	SecondTurnOffCallbackUpdate.BindUFunction(this, FName("DuringFirstTurnOnTick"));
	SecondTurnOffTimeLine.AddInterpFloat(TurnOffCurve, SecondTurnOffCallbackUpdate);
	
	FOnTimelineEventStatic SecondTurnOffCallbackFinisehd;
	SecondTurnOffCallbackFinisehd.BindUFunction(this, FName("OnFirstTurnOnFinished"));
	SecondTurnOffTimeLine.SetTimelineFinishedFunc(SecondTurnOffCallbackFinisehd);

	//----- Second Lights On
	FOnTimelineFloat SecondTurnOnCallbackUpdate;
	SecondTurnOnCallbackUpdate.BindUFunction(this, FName("DuringSecondTurnOnTick"));
	SecondTurnOffTimeLine.AddInterpFloat(TurnOnCurve, SecondTurnOnCallbackUpdate);
	
	FOnTimelineEventStatic SecondTurnOnCallbackFinisehd;
	SecondTurnOnCallbackFinisehd.BindUFunction(this, FName("OnSecondTurnOnFinished"));
	SecondTurnOffTimeLine.SetTimelineFinishedFunc(SecondTurnOnCallbackFinisehd);

	//----- Third Light out
	FOnTimelineFloat ThirdTurnOffCallbackUpdate;
	ThirdTurnOffCallbackUpdate.BindUFunction(this, FName("DuringThirdTurnOffTick"));
	ThirdTurnOffTimeLine.AddInterpFloat(TurnOffCurve, ThirdTurnOffCallbackUpdate);
	
	FOnTimelineEventStatic ThirdTurnOffCallbackFinisehd;
	ThirdTurnOffCallbackFinisehd.BindUFunction(this, FName("OnThirdTurnOffFinished"));
	ThirdTurnOffTimeLine.SetTimelineFinishedFunc(ThirdTurnOffCallbackFinisehd);

	//----- Third Light on
	FOnTimelineFloat ThirdTurnOnCallbackUpdate;
	ThirdTurnOnCallbackUpdate.BindUFunction(this, FName("DuringThirdTurnOnTick"));
	ThirdTurnOnTimeLine.AddInterpFloat(TurnOnCurve, ThirdTurnOnCallbackUpdate);
	
	FOnTimelineEventStatic ThirdTurnOnCallbackFinisehd;
	ThirdTurnOnCallbackFinisehd.BindUFunction(this, FName("OnThirdTurnOnFinished"));
	ThirdTurnOnTimeLine.SetTimelineFinishedFunc(ThirdTurnOnCallbackFinisehd);

	//----- Last Light off
	FOnTimelineFloat LasturnOffCallbackUpdate;
	LasturnOffCallbackUpdate.BindUFunction(this, FName("DuringLastTurnOffTick"));
	LastTurnOffTimeLine.AddInterpFloat(TurnOffCurve, LasturnOffCallbackUpdate);
	
	FOnTimelineEventStatic LasturnOffCallbackFinisehd;
	LasturnOffCallbackFinisehd.BindUFunction(this, FName("OnLastTurnOffFinished"));
	LastTurnOffTimeLine.SetTimelineFinishedFunc(LasturnOffCallbackFinisehd);

	//----- Last Light on
	FOnTimelineFloat LasturnOnCallbackUpdate;
	LasturnOnCallbackUpdate.BindUFunction(this, FName("DuringLastTurnOnTick"));
	LastTurnOnTimeLine.AddInterpFloat(TurnOnCurve, LasturnOnCallbackUpdate);
	
	FOnTimelineEventStatic LasturnOnCallbackFinisehd;
	LasturnOnCallbackFinisehd.BindUFunction(this, FName("OnLastTurnOnFinished"));
	LastTurnOnTimeLine.SetTimelineFinishedFunc(LasturnOnCallbackFinisehd);

}

void ACloclLevelArtRoomEvent::OnEventStarted(AActor* OverlappedActor, AActor* OtherActor)
{
	auto alex = Cast<AAlex>(OtherActor);
	if(!alex) return;
	
	Alex = alex;
	Alex->SetCameraStun(true);

	if(DoOnce != 0) return;

	HearthBeatComponent = UGameplayStatics::SpawnSound2D(this, HeathBeatSFX);
	UGameplayStatics::SpawnSound2D(this, TiffanyNearSFX);
	
	DoOnce++;	
	OnArtRoomEventStarted.Broadcast();

	
	
	UMaterialInstanceDynamic* PostProcessMaterial1 = UMaterialInstanceDynamic::Create(PostProcessMaterialEvent, this);

	originalPostProcessValues = PostProcess->GetProperties();

	PostProcess->AddOrUpdateBlendable(PostProcessMaterial1);
	
	Alex->CameraTargeting(StandTiffany->GetActorLocation());
	
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->DisableInput(controller);
	
	ArtRoomDoor->SetLockedState(true);
	ArtRoomDoor->HardClosing();

	ArtRoomLight->TurnOff();
	UGameplayStatics::SpawnSound2D(this, LightSwitch);
	
	FirstTurnOffTimeLine.PlayFromStart();
}

void ACloclLevelArtRoomEvent::DuringFirstTurnOffTick(float deltaTime) { }

void ACloclLevelArtRoomEvent::FirstTurnOffFinished()
{
	StandTiffany->GetMesh()->SetVisibility(true, false);
	
	UGameplayStatics::SpawnSound2D(this, LightSwitch);
	SpotLight->SpotLightComponent->SetIntensity(60);
	

	FirstTurnOnTimeLine.PlayFromStart();
}

void ACloclLevelArtRoomEvent::DuringFirstTurnOnTick(float deltaTime) { }

void ACloclLevelArtRoomEvent::OnFirstTurnOnFinished()
{
	SpotLight->SpotLightComponent->SetIntensity(0);
	UGameplayStatics::SpawnSound2D(this, LightSwitch);

	StandTiffany->SetActorLocation(RoomCenterTaregtPoint->GetActorLocation());

	FloatingTiff1->GetSkeletalMeshComponent()->SetVisibility(true,false);
	FloatingTiff2->GetSkeletalMeshComponent()->SetVisibility(true, false);

	SecondTurnOffTimeLine.PlayFromStart();
}

void ACloclLevelArtRoomEvent::DuringSecondTurnOnTick(float deltaTime) { }

void ACloclLevelArtRoomEvent::OnSecondTurnOnFinished()
{
	UGameplayStatics::SpawnSound2D(this, LightSwitch);
	SpotLight->SpotLightComponent->SetIntensity(60);

	ThirdTurnOffTimeLine.PlayFromStart();
}

void ACloclLevelArtRoomEvent::DuringThirdTurnOffTick(float deltaTime) { }

void ACloclLevelArtRoomEvent::OnThirdTurnOffFinished()
{
	SpotLight->SpotLightComponent->SetIntensity(0);
	UGameplayStatics::SpawnSound2D(this, LightSwitch);
	
	StandTiffany->SetActorLocation(CloserTargetPoint->GetActorLocation());

	FloatingTiff3->GetSkeletalMeshComponent()->SetVisibility(true, false);
	FloatingTiff4->GetSkeletalMeshComponent()->SetVisibility(true, false);


	ThirdTurnOnTimeLine.PlayFromStart();
}

void ACloclLevelArtRoomEvent::DuringThirdTurnOnTick(float deltaTime) { }

void ACloclLevelArtRoomEvent::OnThirdTurnOnFinished()
{
	UGameplayStatics::SpawnSound2D(this, LightSwitch);
	SpotLight->SpotLightComponent->SetIntensity(60);

	LastTurnOffTimeLine.PlayFromStart();
}

void ACloclLevelArtRoomEvent::DuringLastTurnOffTick(float deltaTime) { }

void ACloclLevelArtRoomEvent::OnLastTurnOffFinished()
{
	SpotLight->SpotLightComponent->SetIntensity(0);
	UGameplayStatics::SpawnSound2D(this, LightSwitch);

	StandTiffany->GetMesh()->SetVisibility(false, false);
	FloatingTiff1->GetSkeletalMeshComponent()->SetVisibility(false, false);
	FloatingTiff2->GetSkeletalMeshComponent()->SetVisibility(false, false);
	FloatingTiff3->GetSkeletalMeshComponent()->SetVisibility(false, false);
	FloatingTiff4->GetSkeletalMeshComponent()->SetVisibility(false, false);

	LastTurnOnTimeLine.PlayFromStart();
}

void ACloclLevelArtRoomEvent::DuringLastTurnOnTick(float deltaTime) { }

void ACloclLevelArtRoomEvent::OnLastTurnOnFinished()
{
	ArtRoomLight->TurnOn();
	UGameplayStatics::SpawnSound2D(this, LightSwitch);
	UGameplayStatics::SpawnSound2D(this, SFXTiffanyTalksToAlex);
	
	ArtRoomDoor->SetLockedState(false);

	OnArtRoomEventFinished.Broadcast();
	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->EnableInput(controller);
	
	HearthBeatComponent->Stop();
	HearthBeatComponent->DestroyComponent();
	
	StartTriggerBox->Destroy();
	
	Alex->SetCameraStun(false);
	
	Destroy();
}

void ACloclLevelArtRoomEvent::BeginPlay()
{
	Super::BeginPlay();

	BindTimeLines();
}

void ACloclLevelArtRoomEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FirstTurnOffTimeLine.TickTimeline(DeltaTime);
	FirstTurnOnTimeLine.TickTimeline(DeltaTime);
	SecondTurnOffTimeLine.TickTimeline(DeltaTime);
	SecondTurnOnTimeLine.TickTimeline(DeltaTime);
	ThirdTurnOffTimeLine.TickTimeline(DeltaTime);
	ThirdTurnOnTimeLine.TickTimeline(DeltaTime);
	LastTurnOffTimeLine.TickTimeline(DeltaTime);
	LastTurnOnTimeLine.TickTimeline(DeltaTime);
}