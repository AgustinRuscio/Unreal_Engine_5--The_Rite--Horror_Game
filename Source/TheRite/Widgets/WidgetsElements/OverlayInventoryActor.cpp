//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "OverlayInventoryActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/PointLightComponent.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AOverlayInventoryActor::AOverlayInventoryActor()
{
 	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	
	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>("Campure component");
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("Point light");

	ItemMesh->SetupAttachment(SceneComponent);
	
	SceneCaptureComponent2D->SetupAttachment(SceneComponent);
	PointLightComponent->SetupAttachment(SceneCaptureComponent2D);
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AOverlayInventoryActor::BeginPlay()
{
	Super::BeginPlay();

	SceneCaptureComponent2D->ShowOnlyActorComponents(this);
}