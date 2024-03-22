#include "SpectralWrittings.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"

void ASpectralWrittings::BeginPlay()
{
	Super::BeginPlay();
	
	Material = Mesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	Mesh->SetMaterial(0, DynamicMaterial);
}

ASpectralWrittings::ASpectralWrittings()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	IdleAudio = CreateDefaultSubobject<UAudioComponent>("Audio");
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	IdleAudio->SetupAttachment(Mesh);
	CollisionBox->SetupAttachment(Mesh);
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

void ASpectralWrittings::SetMaterialAlpha(float alpha)
{
	if(bDiscovered) return;
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),alpha);
}

void ASpectralWrittings::Interaction()
{
	Super::Interaction();
	
	if(bDiscovered) return;
	
	bDiscovered= true;
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), AudioToPlay, GetActorLocation());
	IdleAudio->DestroyComponent();
	
	Mesh->SetVisibility(true);
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),1);
}