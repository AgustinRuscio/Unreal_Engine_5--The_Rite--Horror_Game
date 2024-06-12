//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "FuseBox.h"
#include "Components/ArrowComponent.h"
#include "LightSwitch.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"

AFuseBox::AFuseBox()
{
	PrimaryActorTick.bCanEverTick = true;
	
	FusibleBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>("Fusible Box");
	
	FirstFusible = CreateDefaultSubobject<UStaticMeshComponent>("First Fusible");
	SecondsFusible = CreateDefaultSubobject<UStaticMeshComponent>("Seconds Fusible");
	FirstFusible->SetupAttachment(FusibleBoxMesh);
	SecondsFusible->SetupAttachment(FusibleBoxMesh);

	FirstFusible->SetVisibility(false);
	SecondsFusible->SetVisibility(false);
	
	InitialPosition = CreateDefaultSubobject<UArrowComponent>("Initial position Arrow");
	EndFirstPosition = CreateDefaultSubobject<UArrowComponent>("First End position Arrow");
	EndSecondPosition = CreateDefaultSubobject<UArrowComponent>("Seconds End position Arrow");

	InitialPosition->SetupAttachment(FusibleBoxMesh);
	EndFirstPosition->SetupAttachment(FusibleBoxMesh);
	EndSecondPosition->SetupAttachment(FusibleBoxMesh);
}

//--------------------- System Class methods
void AFuseBox::BeginPlay()
{
	Super::BeginPlay();
	
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("LocateFusibleTick"));
	LocateFusibleTimeLine.AddInterpFloat(LocateFusibleCurve, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("LocateFusibleFinished"));
	LocateFusibleTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

void AFuseBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LocateFusibleTimeLine.TickTimeline(DeltaTime);
}

void AFuseBox::Interaction()
{
	if(!bCanInteract) return;

	if(!bHastFusibleToPut) 
	{
		if(!bBothFusiblesSameTime)
			return;
	}
	
	bCanInteract = false;
	bHastFusibleToPut = false;
	FusiblesQuantity++;

	
	if(FusiblesQuantity == 1)
		FirstFusible->SetVisibility(true);
	else
		SecondsFusible->SetVisibility(true);

	
	auto player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	player->RemoveFromInventory(FusesNames[0], FusesId[0]);

	FusesNames.RemoveAt(0);
	FusesId.RemoveAt(0);
	
	LocateFusibleTimeLine.PlayFromStart();
}

void AFuseBox::GrabFusible(FString FuseName, PickableItemsID FuseId)
{
	FusesNames.Add(FuseName);
	FusesId.Add(FuseId);
	
	if(!bHastFusibleToPut)
		bHastFusibleToPut = true;
	else
		bBothFusiblesSameTime = true;
}

//--------------------- TimeLine methods
void AFuseBox::LocateFusibleTick(float deltaSeconds)
{
	if(FusiblesQuantity == 1)
	{
		auto lerpingPos = FMath::Lerp(InitialPosition->GetRelativeLocation(), EndFirstPosition->GetRelativeLocation(), deltaSeconds);
		
		FirstFusible->SetRelativeLocation(lerpingPos);
	}
	else
	{
		auto lerpingPos = FMath::Lerp(InitialPosition->GetRelativeLocation(), EndSecondPosition->GetRelativeLocation(), deltaSeconds);
		
		SecondsFusible->SetRelativeLocation(lerpingPos);
	}
}

void AFuseBox::LocateFusibleFinished()
{
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_Sparking,GetActorLocation());
	

	if(FusiblesQuantity == 1)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSytem_Sparks, EndFirstPosition->GetComponentLocation());
	else
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSytem_Sparks, EndSecondPosition->GetComponentLocation());
	
	if(MaxFusiblesQuantity == FusiblesQuantity)
	{
		bCanInteract = false;
		OnFuseBoxComplete.Broadcast();
		TermicalSwitch->SetSpecialReady();
	}
	else
	{
		bCanInteract = true;
	}
}