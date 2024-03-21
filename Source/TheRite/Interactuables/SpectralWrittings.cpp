
#include "SpectralWrittings.h"
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
}

bool ASpectralWrittings::GetDiscoverdStatus() const
{
	return bDiscovered;
}

void ASpectralWrittings::Activate() const
{
	Mesh->SetVisibility(true);
}

void ASpectralWrittings::Deactivate() const
{
	Mesh->SetVisibility(false);
}

void ASpectralWrittings::SetMaterialAlpha(float alpha)
{
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),alpha);
}

void ASpectralWrittings::Interaction()
{
	Super::Interaction();
}

