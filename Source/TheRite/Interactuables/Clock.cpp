//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Clock.h"

#include "VectorTypes.h"
#include "Components/PointLightComponent.h"
#include "Engine/PointLight.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AmbientObjects/Candle.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/AmbientObjects/CustomLight.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/LevelsGameFlow/ProsProcessModifier.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AClock::AClock() : MinimumDistanceForPostProces(1000.f), NextLevelName("Credits")
{
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("ClockBase");
	Needles = CreateDefaultSubobject<UStaticMeshComponent>("Needles");
	
	RootComponent = BaseMesh;

	Needles->SetupAttachment(BaseMesh);

	Light= CreateDefaultSubobject<UPointLightComponent>("Light");
	Light->SetupAttachment(BaseMesh);
}

//----------------------------------------------------------------------------------------------------------------------
FName AClock::GetObjectData() const
{
	return NextLevelName;
}

//----------------------------------------------------------------------------------------------------------------------
void AClock::Interaction()
{
	Super::Interaction();
	
	for (auto Element : TurnedOfLights)
	{
		Element->TurnOff();
	}

	for (auto Element : TurnedOfCustomLights)
	{
		Element->TurnOff();
	}

	for (auto Element : ObjCandles)
	{
		Element->Disappear();
	}

	Destroy();
}

//----------------------------------------------------------------------------------------------------------------------
void AClock::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<AAlex>(GetWorld()->GetFirstPlayerController()->GetPawn();
}

//----------------------------------------------------------------------------------------------------------------------
void AClock::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CalculateDistanceWithPlayer();
}

//----------------------------------------------------------------------------------------------------------------------
void AClock::CalculateDistanceWithPlayer()
{
	float DistanceFromPlayer = UE::Geometry::Distance(GetActorLocation(), Player->GetActorLocation());
	
	if(DistanceFromPlayer > MinimumDistanceForPostProces)
	{
		PostProcesModifierClass->ModifyPostProcessValues(PostProcessModiferValue, 0.f);
	}
	else
	{
		float calculatedDistance = ((DistanceFromPlayer / MinimumDistanceForPostProces)*-1) + 1.2f;
		PostProcesModifierClass->ModifyPostProcessValues(PostProcessModiferValue, calculatedDistance);
	}
}