//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

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
	Mesh	       = CreateDefaultSubobject<UStaticMeshComponent>("Candle Mesh");
	Plane	       = CreateDefaultSubobject<UStaticMeshComponent>("Plane Mesh");
	PointLight	   = CreateDefaultSubobject<UPointLightComponent>("Light");
	SmokeParticles = CreateDefaultSubobject<UNiagaraComponent>("Smoke particles");

	Plane->SetupAttachment(Mesh);
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
	Mesh->SetHiddenInGame(false);
	Plane->SetVisibility(true);
	PointLight->SetVisibility(true);
}

//----------------------------------------------------------------------------------------------------------------------
void ACandle::Disappear() const
{
	Mesh->SetVisibility(false);
	Mesh->SetHiddenInGame(true);
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

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();	
}

//----------------------------------------------------------------------------------------------------------------------
void ACandle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bProximityTurnedOff || Mesh->bHiddenInGame || bTurnOffProximityDoOnce || !Player) return;

	if (FVector::Dist(GetActorLocation(), Player->GetActorLocation()) <= TurnOffDistance)
	{
		TurnOff();
		bTurnOffProximityDoOnce = true;
	}
}