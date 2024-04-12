//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "SpectralWrittings.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/LevelsGameFlow/ClockLevelGameFlow.h"

void ASpectralWrittings::BeginPlay()
{
	Super::BeginPlay();
	
	Material = Mesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	Mesh->SetMaterial(0, DynamicMaterial);


	bReady = true;

	
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetVisibility(false);
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
	
	if(!bPlayerInside || bDiscovered) return;
	float DistanceToCenter = FVector::Dist(InsideActor->GetActorLocation(), GetActorLocation());
	
	float NormalizedDistance = FMath::Clamp(DistanceToCenter/Sphere->GetScaledSphereRadius(), 0.f, 1.f);
	
	float AlphaValue = FMath::Lerp(1.f, 0.f, NormalizedDistance);
	
	Gameflow->ModifyPostProcessValues(PostProcessToModifyParameterName, AlphaValue);
}

bool ASpectralWrittings::GetDiscoverdStatus() const
{
	return bDiscovered;
}

void ASpectralWrittings::Activate() const
{
	if(bDiscovered) return;
	
	Mesh->SetVisibility(true);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ASpectralWrittings::Deactivate() const
{
	if(bDiscovered) return;
	
	Mesh->SetVisibility(false);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASpectralWrittings::EnableInteraction()
{
	bCanInteract = true;
}

void ASpectralWrittings::SetMaterialAlpha(float alpha)
{
	if(bDiscovered) return;
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),alpha);
}

void ASpectralWrittings::Discovered()
{
	bDiscovered= true;
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	IdleAudio->DestroyComponent();
	
	Mesh->SetVisibility(true);
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),1);

	Gameflow->ModifyPostProcessValues(PostProcessToModifyParameterName, 0);
}

void ASpectralWrittings::Interaction()
{
	if(bDiscovered || !bCanInteract) return;
	
	Super::Interaction();
	
	bCanInteract = false;
	bDiscovered= true;
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SpectralSound, GetActorLocation(), FRotator::ZeroRotator, 0.2f);
	
	IdleAudio->DestroyComponent();
	
	Mesh->SetVisibility(true);
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),1);
	
	Gameflow->ModifyPostProcessValues(PostProcessToModifyParameterName, 0);
}