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

//*****************************Public********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AAltar::AAltar()
{
 	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

//----------------------------------------------------------------------------------------------------------------------
void AAltar::Interaction()
{
	if(bIsFocus || !bCanInteract) return;
	
	bIsFocus = true;

	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetFocusInput();

	controller->OnPrevInventoryItem.AddDynamic(this, &AAltar::PrevWheel);
	controller->OnNextInventoryItem.AddDynamic(this, &AAltar::NextWheel);
	controller->OnInteractionPressed.AddDynamic(this, &AAltar::WheelInteraction);
	controller->OnLeaveFocus.AddDynamic(this, &AAltar::LeaveFocus);

	for (auto Element : Whells)
	{
		Element->EnableInteraction();
	}
	
	Player->OnFocusMode(CameraPos[WhellIndex]->GetActorTransform(), ExittingRotation, true);
}

//----------------------------------------------------------------------------------------------------------------------
void AAltar::DisableAltarInteraction()
{
	DisableInteraction();
}

//*****************************Private********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AAltar::BeginPlay()
{
	Super::BeginPlay();

	Player = CastChecked<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	BindTimeLine();
}

//----------------------------------------------------------------------------------------------------------------------
void AAltar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCameraTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void AAltar::DisableInteraction()
{
	bCanInteract = false;
}

//----------------------------------------------------------------------------------------------------------------------
void AAltar::LeaveFocus()
{
	if(!bCanInteract || Player->GetFocusingState()) return;
	
	bIsFocus = false;
	Player->BackToNormalView(CameraPos[WhellIndex]->GetActorTransform(), ExittingVector, ExittingRotation);
	
	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetNormalInput();

	controller->OnPrevInventoryItem.RemoveDynamic(this, &AAltar::PrevWheel);
	controller->OnNextInventoryItem.RemoveDynamic(this, &AAltar::NextWheel);
	controller->OnInteractionPressed.RemoveDynamic(this, &AAltar::WheelInteraction);
	controller->OnLeaveFocus.RemoveDynamic(this, &AAltar::LeaveFocus);
	
	for (auto Element : Whells)
	{
		Element->DisableInteraction();
	}
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Actions methods
void AAltar::WheelInteraction()
{
	if(!bCanInteract || Player->GetFocusingState()) return;
	
	Whells[WhellIndex]->Interaction();
}

//----------------------------------------------------------------------------------------------------------------------
void AAltar::PrevWheel()
{
	if(!bCanInteract || Player->GetFocusingState()) return;
	
	--WhellIndex;

	if(WhellIndex < 0)
		WhellIndex = Whells.Num()-1;
	
	ChangeCameraPosition();
}

//----------------------------------------------------------------------------------------------------------------------
void AAltar::NextWheel()
{
	if(!bCanInteract || Player->GetFocusingState()) return;
	
	++WhellIndex;
	
	if(WhellIndex >=  Whells.Num())
		WhellIndex = 0;

	ChangeCameraPosition();
}

//----------------------------------------------------------------------------------------------------------------------
void AAltar::ChangeCameraPosition()
{
	bCanInteract = false;
	cameraPos = Player->GetCamera()->GetComponentLocation();
	MoveCameraTimeLine.PlayFromStart();
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region TimeLine methods
void AAltar::BindTimeLine()
{
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("MoveCameraTick"));
	MoveCameraTimeLine.AddInterpFloat(CurveFloat, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("MoveCameraFinished"));
	MoveCameraTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void AAltar::MoveCameraTick(float deltaSecinds)
{
	auto newX = FMath::Lerp(cameraPos, CameraPos[WhellIndex]->GetActorLocation(), deltaSecinds);
	
	Player->MoveCamera(newX);
}

//----------------------------------------------------------------------------------------------------------------------
void AAltar::MoveCameraFinished()
{
	bCanInteract = true;
}
#pragma endregion 