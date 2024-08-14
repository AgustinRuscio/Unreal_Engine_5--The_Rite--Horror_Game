//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Candle.h"

#include "NiagaraComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

//*****************************Public******************************************
//******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------
void ACandle::TurnOn() const
{
	PointLight->SetVisibility(true);
	Plane->SetVisibility(true);
}

//----------------------------------------------------------------------------------------------------------------------
void ACandle::TurnOff() const
{
	SmokeParticles->Activate();
	PointLight->SetVisibility(false);
	Plane->SetVisibility(false);

	if(bWillSound)
		UGameplayStatics::PlaySoundAtLocation(this, BlowCandleSound, GetActorLocation(), GetActorRotation());
}

//----------------------------------------------------------------------------------------------------------------------
void ACandle::Appear() const
{
	Mesh->SetVisibility(true);
	Plane->SetVisibility(true);
	PointLight->SetVisibility(true);
}

//----------------------------------------------------------------------------------------------------------------------
void ACandle::Disappear() const
{
	Mesh->SetVisibility(false);
	Plane->SetVisibility(false);
	PointLight->SetVisibility(false);
}

//*****************************Private******************************************
//******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ACandle::BeginPlay()
{
	Super::BeginPlay();

	bStartsTurnedOn ? TurnOn() : TurnOff();
}