//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "WalkerTiffany.h"

#include "LightsTheRite.h"
#include "VectorTypes.h"
#include "Components/BoxComponent.h"
#include "Components/LightComponent.h"
#include "Engine/PointLight.h"
#include "Engine/SpotLight.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Characters/Tiffany.h"
#include "TheRite/Interactuables/Door.h"

//----------------------------------------------------------------------------------------------------------------------
AWalkerTiffany::AWalkerTiffany() : bReadyToWalk(true), bUseLights(false), bDoOnce(false), AcceptanceDistance(0.f)
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWalkerTiffany::OnOverlapBegin);
}

//----------------------------------------------------------------------------------------------------------------------
void AWalkerTiffany::Activate()
{
	WalkerTiffany->Activate();
	bReadyToWalk = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AWalkerTiffany::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;

	WalkerTiffany =GetWorld()->SpawnActor<ATiffany>(DetectorSubclass.Get(), SpawnTargetPoint->GetActorLocation(), SpawnTargetPoint->GetActorRotation(), SpawnParams);

	if(WalkerTiffany)
	{
		WalkerTiffany->SetActorLocation(SpawnTargetPoint->GetActorLocation());
		WalkerTiffany->SetActorRotation(SpawnTargetPoint->GetActorRotation());
		WalkerTiffany->SetData(true, false, true, bTiffanyCrawl);
		WalkerTiffany->Deactivate();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("No tifany seted")));
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AWalkerTiffany::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	TimerHandle.Invalidate();
	GetWorldTimerManager().ClearTimer(TimerHandle);
	
	TimerDelegate.Unbind();
}

//----------------------------------------------------------------------------------------------------------------------
void AWalkerTiffany::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bDoOnce)
	{
		if(UE::Geometry::Distance(WalkerTiffany->GetActorLocation(), DesiredTargetPoint->GetActorLocation()) <= AcceptanceDistance)
		{
			bDoOnce = false;
			if(OpeningDoors.Num() > 0)
			{
				for (auto Element : OpeningDoors)
				{
					Element->HardClosing();
				}
			}

			if(bUseLights)
				LightsOff();
			else
				Destroy();
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AWalkerTiffany::LightsOff()
{
	if(TheRiteLights.Num()>0)
	{
		for (auto Element : TheRiteLights)
		{
			Element->TurnOff();
		}
	}
	
	if(SpotLights.Num()>0)
	{
		for (auto Element : SpotLights)
		{
			spotIntensities.Add(Element->GetLightComponent()->Intensity);
			Element->GetLightComponent()->SetIntensity(0.f);
		}
	}

	if(!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
	{
		TimerDelegate.BindLambda([&]
		{
			LightsOn();
		});
		
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 2.f, false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AWalkerTiffany::LightsOn()
{
	for (auto Element : TheRiteLights)
	{
		Element->TurnOn();
	}

	for (int i = 0; i< SpotLights.Num()-1 ; i++ )
	{
		SpotLights[i]->GetLightComponent()->SetIntensity(spotIntensities[i]);
	}
	
	spotIntensities.Empty();
	
	Destroy();
}

//----------------------------------------------------------------------------------------------------------------------
void AWalkerTiffany::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AAlex>(OtherActor) || bDoOnce || !bReadyToWalk) return;

	bDoOnce = true;
	
	WalkerTiffany->Activate();
	WalkerTiffany->StartMovement(DesiredTargetPoint);

	if(OpeningDoors.Num() <= 0) return;
	UGameplayStatics::PlaySound2D(GetWorld(), OpenDoorSound);
	
	for (auto Element : OpeningDoors)
	{
		Element->Open();
	}
}