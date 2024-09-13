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
#include "TheRite/Characters/Alex.h"
#include "TheRite/LevelsGameFlow/ProsProcessModifier.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AClock::AClock()
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
AClock::~AClock()
{
	OnInteractionTrigger.Clear();
}

//----------------------------------------------------------------------------------------------------------------------
FName AClock::GetObjectData() const
{
	return NextLevelName;
}

//----------------------------------------------------------------------------------------------------------------------
void AClock::Interaction()
{
	
	if(bTest)
	{
		for (auto Element : TurnedOfLights)
		{
			Element->TurnOff();
		}

		for (auto Element : ObjCandles)
		{
			Element->Disappear();
		}

		Super::Interaction();
		Destroy();
	}
	else
	{
		
		OnInteractionTrigger.Broadcast(this);
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());
		Destroy();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AClock::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
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