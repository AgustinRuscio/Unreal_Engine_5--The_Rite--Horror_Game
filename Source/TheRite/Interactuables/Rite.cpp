//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Rite.h"

#include "Components/PostProcessComponent.h"
#include "Components/SphereComponent.h"
#include "Clock.h"
#include "Components/AudioComponent.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Characters/Alex.h"


ARite::ARite()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Plane");
	IdleAudio = CreateDefaultSubobject<UAudioComponent>("Audio");
	Sphere = CreateDefaultSubobject<USphereComponent>("Detector");
	
	
	RootComponent = Mesh;
	IdleAudio->SetupAttachment(Mesh);
	Sphere->SetupAttachment(Mesh);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARite::OnActorOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ARite::OnActorOverapFinished);
}

//---------------- System Class Methods
void ARite::BeginPlay()
{
	Super::BeginPlay();

	CheckAudio();
	
	DynamicMaterial = UMaterialInstanceDynamic::Create(PostProcesRealWorldMaterial, this);
	OriginalPostProcessValues = PostProcessComponent->GetProperties();
	PostProcessComponent->AddOrUpdateBlendable(DynamicMaterial);
	bReady = true;

	CurrentMainObject->OnInteractionTrigger.AddDynamic(this, &ARite::SetClockReady);
}

void ARite::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(!bPlayerInside && bReady) return;
	
	float DistanceToCenter = FVector::Dist(InsideActor->GetActorLocation(), GetActorLocation());
	
	float NormalizedDistance = FMath::Clamp(DistanceToCenter/Sphere->GetScaledSphereRadius(), 0.f, 1.f);
	
	float AlphaValue = FMath::Lerp(1.f, 0.f, NormalizedDistance);

	
	DynamicMaterial->SetScalarParameterValue(TEXT("SpectralProximity"),AlphaValue);
}

void ARite::Interaction()
{
	if(!bObjectReady) return;
	
	UGameplayStatics::PlaySound2D(this, PortalAudio);

	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.PlayRate = 1.0f; 
	PlaybackSettings.bAutoPlay = true;
	PlaybackSettings.bRandomStartTime = false;

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->DisableInput(controller);
	
	ALevelSequenceActor* TempLevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	
	ULevelSequencePlayer* sequencePlayer =  ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceFade,
																				PlaybackSettings,TempLevelSequenceActor);

	sequencePlayer->OnFinished.AddDynamic(this, &ARite::ChangeLevel);
	
	sequencePlayer->Play();
}

void ARite::SetClockReady(AInteractor* obj)
{
	bObjectReady = true;
	CheckAudio();
	NextLevel = CurrentMainObject->GetObjectData();
}

void ARite::CheckAudio()
{
	if(bObjectReady)
		AudioToPlay = AudioClockReady;
	else
	{
		switch (LevelType)
		{
			case LevelObjectType::Clock:
				AudioToPlay = AudioClockNotReady;
				break;
			case LevelObjectType::Picture:
				AudioToPlay = AudioClockNotReady;
				break;
			case LevelObjectType::Diary:
				AudioToPlay = AudioClockNotReady;
				break;
		}
	}
}

void ARite::ChangeLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(),NextLevel);
}

void ARite::OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if(!Cast<AAlex>(Actor)) return;

	InsideActor = Actor;
	bPlayerInside = true;
}

void ARite::OnActorOverapFinished(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I)
{
	if(!Cast<AAlex>(Actor)) return;
	
	bPlayerInside = false;
	InsideActor = nullptr;
}