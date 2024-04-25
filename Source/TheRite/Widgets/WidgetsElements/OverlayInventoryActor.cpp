//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "OverlayInventoryActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/PointLightComponent.h"

AOverlayInventoryActor::AOverlayInventoryActor()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>("Campure component");
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("Point light");

	SceneCaptureComponent2D->SetupAttachment(ItemMesh);
	PointLightComponent->SetupAttachment(SceneCaptureComponent2D);
}

void AOverlayInventoryActor::BeginPlay()
{
	Super::BeginPlay();

	SceneCaptureComponent2D->ShowOnlyActorComponents(this);
}