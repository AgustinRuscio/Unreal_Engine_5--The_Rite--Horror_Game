//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Candle.h"

#include "NiagaraComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

ACandle::ACandle()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Candle Mesh");
	Plane = CreateDefaultSubobject<UStaticMeshComponent>("Plane Mesh");
	PointLight = CreateDefaultSubobject<UPointLightComponent>("Light");
	SmokeParticles = CreateDefaultSubobject<UNiagaraComponent>("Smoke particles");

	Plane ->SetupAttachment(Mesh);
	PointLight->SetupAttachment(Mesh);
	SmokeParticles->SetupAttachment(Mesh);
}

void ACandle::BeginPlay()
{
	Super::BeginPlay();

	bStartsTurnedOn ? TurnOn() : TurnOff();
}

void ACandle::TurnOn()
{
	PointLight->SetVisibility(true);
	Plane->SetVisibility(true);
}

void ACandle::TurnOff()
{
	SmokeParticles->Activate();
	PointLight->SetVisibility(false);
	Plane->SetVisibility(false);

	if(bWillSound)
		UGameplayStatics::PlaySoundAtLocation(this, BlowCandleSound, GetActorLocation(), GetActorRotation());
}

void ACandle::Appear()
{
	Mesh->SetVisibility(true);
	Plane->SetVisibility(true);
	PointLight->SetVisibility(true);
}

void ACandle::Disappear()
{
	Mesh->SetVisibility(false);
	Plane->SetVisibility(false);
	PointLight->SetVisibility(false);
}