//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.3						//
//----------------------------------------------//

#include "DeathTiffany.h"
#include "Components/ArrowComponent.h"
#include <TheRite/Characters/Alex.h>

namespace
{
	FVector PlayerOnTimeLocation;
}

//----------------------------------------------------------------------------------------------------------------------
ADeathTiffany::ADeathTiffany() : bHasPillow(false), PillowInitialLocation(0,0,0)
{
 	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Body Mesh");
	RootComponent = BodyMesh;

	PillowMesh = CreateDefaultSubobject<UStaticMeshComponent>("Pillow Mesh");
	PillowMesh->SetupAttachment(BodyMesh);
}

//----------------------------------------------------------------------------------------------------------------------
void ADeathTiffany::Interaction()
{
	if(!bCanInteract) return;

	auto player = Cast<AAlex>(GetWorld()->GetFirstPlayerController()->GetPawn());


	if (bHasPillow)
	{
		bCanInteract = false;
		PillowInitialLocation = PillowMesh->GetComponentLocation();
		PlayerOnTimeLocation = player->GetActorLocation();
		PillowMesh->SetVisibility(true);
		PillowTimeLine.PlayFromStart();

		player->ForceTalk(PillowPlaced);
	}
	else
	{
		player->ForceTalk(NotReadyPillow);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ADeathTiffany::SetPillowReady()
{
	bHasPillow = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ADeathTiffany::BeginPlay()
{
	Super::BeginPlay();

	PillowMesh->SetVisibility(false);

	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("PillowTimeLineTick"));
	PillowTimeLine.AddInterpFloat(PillowCurveFloat, CameraTargetTick);

	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("PillowTimeLineFinish"));
	PillowTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void ADeathTiffany::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PillowTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void ADeathTiffany::PillowTimeLineTick(float deltaSeconds)
{
	auto lerpPos = FMath::Lerp(PlayerOnTimeLocation, PillowInitialLocation, deltaSeconds);
	PillowMesh->SetWorldLocation(lerpPos);
}

//----------------------------------------------------------------------------------------------------------------------
void ADeathTiffany::PillowTimeLineFinish()
{
	BodyMesh->PlayAnimation(DeathAnim, false);
	OnInteractionTrigger.Broadcast(this);
}