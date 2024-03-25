#include "Candle.h"

#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

ACandle::ACandle()
{
 	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Candle Mesh");
	Plane = CreateDefaultSubobject<UStaticMeshComponent>("Plane Mesh");
	PointLight = CreateDefaultSubobject<UPointLightComponent>("Light");

	Plane ->SetupAttachment(Mesh);
	PointLight->SetupAttachment(Mesh);
}

void ACandle::TurnOn()
{
	PointLight->SetVisibility(true);
	Plane->SetVisibility(true);
}

void ACandle::TurnOff()
{
	PointLight->SetVisibility(false);
	Plane->SetVisibility(false);

	if(bWillSound)
		UGameplayStatics::PlaySoundAtLocation(this, BlowCandleSound, GetActorLocation(), GetActorRotation());
	
}