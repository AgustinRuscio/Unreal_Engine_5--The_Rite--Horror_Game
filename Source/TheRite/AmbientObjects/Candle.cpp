#include "Candle.h"

#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

void ACandle::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(MyInteractor))
	MyInteractor->OnInteractionTrigger.AddDynamic(this, &ACandle::EventReady);
}

ACandle::ACandle()
{
 	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Candle Mesh");
	Plane = CreateDefaultSubobject<UStaticMeshComponent>("Plane Mesh");
	PointLight = CreateDefaultSubobject<UPointLightComponent>("Light");

	Plane ->SetupAttachment(Mesh);
	PointLight->SetupAttachment(Mesh);
}

void ACandle::EventReady()
{
	if(!bWillTurnOff) return;

	UGameplayStatics::PlaySoundAtLocation(this, BlowCandleSound, GetActorLocation(), GetActorRotation());
	PointLight->DestroyComponent();
	Plane->DestroyComponent();
}