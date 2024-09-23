//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "OverlayInventoryActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"

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
	DeActivate();

	PlayerRef = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	PlayerRef->OnInventoryOpen.AddDynamic(this, &AOverlayInventoryActor::Activate);
	PlayerRef->OnInventoryClose.AddDynamic(this, &AOverlayInventoryActor::DeActivate);
}

//----------------------------------------------------------------------------------------------------------------------
void AOverlayInventoryActor::Activate()
{
	SceneCaptureComponent2D->SetComponentTickEnabled(true);
	SceneCaptureComponent2D->SetVisibility(true);
	SceneCaptureComponent2D->Activate();
}

//----------------------------------------------------------------------------------------------------------------------
void AOverlayInventoryActor::DeActivate()
{
	SceneCaptureComponent2D->SetComponentTickEnabled(false);
	SceneCaptureComponent2D->SetVisibility(false);
	SceneCaptureComponent2D->Deactivate();
}