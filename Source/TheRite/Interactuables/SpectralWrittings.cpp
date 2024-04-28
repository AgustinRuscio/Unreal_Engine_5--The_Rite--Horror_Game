//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "SpectralWrittings.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "TheRite/LevelsGameFlow/ProsProcessModifier.h"
#include "MathUtil.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TheRite/Characters/Alex.h"

void ASpectralWrittings::BeginPlay()
{
	Super::BeginPlay();
	
	Material = Mesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	Mesh->SetMaterial(0, DynamicMaterial);


	bReady = true;

	
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),0);


	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("FadeTick"));
	FadeTimeLine.AddInterpFloat(FadeCurve, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("FadeFinished"));
	FadeTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

void ASpectralWrittings::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AAlex>(OtherActor)) return;

	InsideActor = OtherActor;
	bPlayerInside = true;
}

void ASpectralWrittings::OnActorOverapFinished(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(!Cast<AAlex>(OtherActor)) return;
	
	bPlayerInside = false;
	InsideActor = nullptr;
}

void ASpectralWrittings::FadeTick(float deltaSeconds)
{
	float value = FMathf::Lerp(0,0.7f,deltaSeconds);
	
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),value);
}

void ASpectralWrittings::FadeFinished()
{
	bFading = false;
}

ASpectralWrittings::ASpectralWrittings()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	IdleAudio = CreateDefaultSubobject<UAudioComponent>("Audio");
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sphere = CreateDefaultSubobject<USphereComponent>("Detector");
	
	IdleAudio->SetupAttachment(Mesh);
	CollisionBox->SetupAttachment(Mesh);
	Sphere->SetupAttachment(Mesh);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASpectralWrittings::OnActorOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ASpectralWrittings::OnActorOverapFinished);
}

ASpectralWrittings::~ASpectralWrittings()
{
	OnInteractionTrigger.Clear();
}

void ASpectralWrittings::BeginDestroy()
{
	Super::BeginDestroy();
	OnInteractionTrigger.Clear();
}

void ASpectralWrittings::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FadeTimeLine.TickTimeline(DeltaSeconds);
	
	if(!bPlayerInside || bDiscovered || bFading) return;
	float DistanceToCenter = FVector::Dist(InsideActor->GetActorLocation(), GetActorLocation());
	
	float NormalizedDistance = FMath::Clamp(DistanceToCenter/Sphere->GetScaledSphereRadius(), 0.f, 1.f);
	
	AlphaValue = FMath::Lerp(1.f, 0.f, NormalizedDistance);
	
	Gameflow->ModifyPostProcessValues(PostProcessToModifyParameterName, AlphaValue);
}

bool ASpectralWrittings::GetDiscoverdStatus() const
{
	return bDiscovered;
}

void ASpectralWrittings::Activate()
{
	if(bDiscovered) return;

	bFading = true;
	
	FadeTimeLine.Stop();
	FadeTimeLine.PlayFromStart();
	
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ASpectralWrittings::Deactivate()
{
	if(bDiscovered) return;
	
	bFading = true;
	FadeTimeLine.Stop();
	LastAlphaValue = AlphaValue;

	FadeTimeLine.ReverseFromEnd();
	
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASpectralWrittings::EnableInteraction()
{
	bCanInteract = true;
}

void ASpectralWrittings::SetMaterialAlpha(float alpha)
{
	if(bDiscovered || bFading) return;
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),alpha);
}

void ASpectralWrittings::Discovered()
{
	bDiscovered= true;
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	IdleAudio->VolumeMultiplier = 0;
	
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),1);

	Gameflow->ModifyPostProcessValues(PostProcessToModifyParameterName, 0);
}

void ASpectralWrittings::Interaction()
{
	if(bDiscovered || !bCanInteract ) return;
	
	Super::Interaction();
	
	bCanInteract = false;
	bDiscovered= true;
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SpectralSound, GetActorLocation(), FRotator::ZeroRotator, 0.2f);
	
	IdleAudio->VolumeMultiplier = 0;
	
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),1);
	
	Gameflow->ModifyPostProcessValues(PostProcessToModifyParameterName, 0);
}