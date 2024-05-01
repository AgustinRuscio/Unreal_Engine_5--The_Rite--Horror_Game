//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Altar.h"
#include "TheRite/Characters/Alex.h"
#include "AltarWhell.h"
#include "Engine/TargetPoint.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"	
#include "TheRite/AlexPlayerController.h"

#define PRINTONVIEWPORT(X) GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT(X)));

//--------------------- Class methods
AAltar::AAltar()
{
 	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
}

void AAltar::BeginPlay()
{
	Super::BeginPlay();

	Player = CastChecked<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	BindTimeLine();
}

void AAltar::BindTimeLine()
{
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("MoveCameraTick"));
	MoveCameraTimeLine.AddInterpFloat(CurveFloat, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("MoveCameraFinished"));
	MoveCameraTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}


void AAltar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCameraTimeLine.TickTimeline(DeltaTime);
}

//------------------------------------

//--------------------- Focus methods

void AAltar::Interaction()
{
	if(bIsFocus) return;
	
	bIsFocus = true;
	Player->OnFocusMode(CameraPos[WhellIndex]->GetActorLocation(), CameraPos[WhellIndex]->GetActorRotation());

	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetFocusInput();

	controller->OnPrevInventoryItem.AddDynamic(this, &AAltar::PrevWhell);
	controller->OnNextInventoryItem.AddDynamic(this, &AAltar::NextWhell);
	controller->OnInteractionPressed.AddDynamic(this, &AAltar::WhellInteraction);
	controller->OnLeaveFocus.AddDynamic(this, &AAltar::LeaveFocus);

	for (auto Element : Whells)
	{
		Element->EnableInteraction();
	}
}

void AAltar::LeaveFocus()
{
	if(!bCanInteract) return;
	
	bIsFocus = false;
	Player->BackToNormalView();
	
	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetNormalInput();

	controller->OnPrevInventoryItem.RemoveDynamic(this, &AAltar::PrevWhell);
	controller->OnNextInventoryItem.RemoveDynamic(this, &AAltar::NextWhell);
	controller->OnInteractionPressed.RemoveDynamic(this, &AAltar::WhellInteraction);
	controller->OnLeaveFocus.RemoveDynamic(this, &AAltar::LeaveFocus);
	
	for (auto Element : Whells)
	{
		Element->DisableInteraction();
	}
}

//------------------------------------

//--------------------- Objects methods

void AAltar::WhellInteraction()
{
	if(!bCanInteract) return;
	
	Whells[WhellIndex]->Interaction();
}

void AAltar::NextWhell()
{
	if(!bCanInteract) return;
	
	++WhellIndex;
	
	if(WhellIndex >=  Whells.Num())
		WhellIndex = 0;

	ChangeCameraPosition();
}


void AAltar::PrevWhell()
{
	if(!bCanInteract) return;
	
	--WhellIndex;

	if(WhellIndex < 0)
		WhellIndex = Whells.Num()-1;
	
	ChangeCameraPosition();
}


void AAltar::ChangeCameraPosition()
{
	bCanInteract = false;
	cameraPos = Player->GetCamera()->GetComponentLocation();
	MoveCameraTimeLine.PlayFromStart();
}

//------------------------------------

//--------------------- TimeLine methods

void AAltar::MoveCameraTick(float deltaSecinds)
{
	auto newX = FMath::Lerp(cameraPos, CameraPos[WhellIndex]->GetActorLocation(), deltaSecinds);
	
	FVector newPos = FVector(cameraPos.X, cameraPos.Y, cameraPos.Z);

	Player->MoveCamera(newX);
}

void AAltar::MoveCameraFinished()
{
	bCanInteract = true;
}
//------------------------------------