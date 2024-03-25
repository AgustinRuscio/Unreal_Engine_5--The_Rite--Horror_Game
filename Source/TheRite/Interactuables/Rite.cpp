#include "Rite.h"

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

void ARite::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(!bPlayerInside && bReady) return;
	
	float DistanceToCenter = FVector::Dist(InsideActor->GetActorLocation(), GetActorLocation());
	
	float NormalizedDistance = FMath::Clamp(DistanceToCenter/Sphere->GetScaledSphereRadius(), 0.f, 1.f);
	
	float AlphaValue = FMath::Lerp(1.f, 0.f, NormalizedDistance);

	
	DynamicMaterial->SetScalarParameterValue(TEXT("SpectralProximity"),AlphaValue);
}

void ARite::BeginPlay()
{
	Super::BeginPlay();
	
	OnClockGain.AddDynamic(this, &ARite::CheckAudio);
	OnClockGain.Broadcast();
	
	DynamicMaterial = UMaterialInstanceDynamic::Create(PostProcesRealWorldMaterial, this);
	OriginalPostProcessValues = PostProcessComponent->GetProperties();
	PostProcessComponent->AddOrUpdateBlendable(DynamicMaterial);
	bReady = true;
}

void ARite::Interaction()
{
	if(!bClockReady) return;
	
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

void ARite::SetClockReady()
{
	bClockReady = true;
}

void ARite::CheckAudio()
{
	if(bClockReady)
		AudioToPlay = AudioClockReady;
	else
		AudioToPlay = AudioClockNotReady;
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
