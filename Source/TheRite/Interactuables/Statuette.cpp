//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Statuette.h"
#include "Engine/StaticMeshActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"

//*****************************Public************************************************
//***********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AStatuette::AStatuette()
{
 	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Getter Methods
bool AStatuette::IsFirstInteraction() const
{
	return bFirstInteraction;
}

//----------------------------------------------------------------------------------------------------------------------
float AStatuette::GetDesiredRotation() const
{
	return DesireRotation;
}

//----------------------------------------------------------------------------------------------------------------------
float AStatuette::GetRotationToAdd() const
{
	return RotationToAdd;
}

//----------------------------------------------------------------------------------------------------------------------
FRotator AStatuette::GetRotation() const
{
	return GetActorRotation();
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
void AStatuette::Interaction()
{	
	if(!bCanInteract) return;

	if(bFirstInteraction)
	{
		bCanInteract = false;
		
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());
		DynamicMaterial->SetScalarParameterValue(TEXT("Interaction"),0);
	}
	else
	{
		bCanInteract = false;
		
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), InteractionSound, GetActorLocation());
		InteractionTimeLine.PlayFromStart();
	}
	
	OnInteractionTrigger.Broadcast(this);
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Setter Methods
void AStatuette::SetAltarPosition(FVector pos, FRotator rot)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorLocation(pos);
	SetActorRotation(rot);
	
	InitialObjectPosition = GetActorLocation();
	EndLocation = InitialObjectPosition + MoveDir;

	InitialBasePosition = BaseMesh->GetActorLocation();
	EndBaseLocation = InitialBasePosition + MoveDir;
	
	BindTimeLine();
	bFirstInteraction = false;
}

//----------------------------------------------------------------------------------------------------------------------
void AStatuette::SetBase(AStaticMeshActor* base)
{
	BaseMesh = base;
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region Action Methods
void AStatuette::EnableInteraction()
{
	bCanInteract = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AStatuette::RestoreInitialValues()
{
	bCanInteract = true;
	InteractionTimeLine.ReverseFromEnd();
}
#pragma endregion 

//*****************************Private************************************************
//************************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AStatuette::BeginPlay()
{
	Super::BeginPlay();

	Material = StaticMesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	StaticMesh->SetMaterial(0, DynamicMaterial);
	DynamicMaterial->SetScalarParameterValue(TEXT("Interaction"),1);
}

//----------------------------------------------------------------------------------------------------------------------
void AStatuette::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	InteractionTimeLine.TickTimeline(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region TimeLine Methods
void AStatuette::BindTimeLine()
{
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OpenTimeLineTick"));
	InteractionTimeLine.AddInterpFloat(TimeLineCurve, TimelineCallback);
}

//----------------------------------------------------------------------------------------------------------------------
void AStatuette::OpenTimeLineTick(float value)
{
	FVector statuettePos = FMath::Lerp(InitialObjectPosition,EndLocation, value);
	FVector basePos = FMath::Lerp(InitialBasePosition,EndBaseLocation, value);
	auto matValue = FMath::Lerp(0,1, value);

	DynamicMaterial->SetScalarParameterValue(TEXT("Interaction"),matValue);
	
	SetActorLocation(statuettePos);
	BaseMesh->SetActorLocation(basePos);
}
#pragma endregion