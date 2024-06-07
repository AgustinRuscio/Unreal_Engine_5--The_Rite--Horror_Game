//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "MoveTiffany.h"
#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Characters/Tiffany.h"
#include "TheRite/Characters/Alex.h"

class AAlex;

AMoveTiffany::AMoveTiffany()
{
 	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	Box->OnComponentBeginOverlap.AddDynamic(this, &AMoveTiffany::OnOverlapBegin);
}

void AMoveTiffany::BeginPlay()
{
	Super::BeginPlay();

	Player = CastChecked<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AMoveTiffany::AsignTiffany(ATiffany* newTiff)
{
	Tiffany = newTiff;
	bActionReady = true;
}

//---------------- Timelines Methods
void AMoveTiffany::FirstTurnOn()
{
	if(InGameSportLight)
	{
		InGameSportLight->GetLightComponent()->SetIntensity(SpotLightIntensity);
		
	}
	else
	{
		for (auto Element : OtherLights)
		{
			Element->TurnOn();
		}
	}

	if(SuddenSound)
		UGameplayStatics::SpawnSound2D(GetWorld(), SuddenSound);
	
	if(!GetWorldTimerManager().IsTimerActive(SecondTurnLightsOff))
		GetWorldTimerManager().SetTimer(SecondTurnLightsOff, this, &AMoveTiffany::SecondTurnOff, .75f, false);
}

void AMoveTiffany::SecondTurnOff()
{

	if(InGameSportLight)
	{
		InGameSportLight->GetLightComponent()->SetIntensity(0.f);
	}
	else
	{
		for (auto Element : OtherLights)
		{
			Element->TurnOff();
		}
	}
	
	if (!GetWorldTimerManager().IsTimerActive(FirstWait))
	{
		FTimerDelegate WaitDelegate;
		WaitDelegate.BindLambda([&]
		{
			Tiffany->Destroy();

			if (!GetWorldTimerManager().IsTimerActive(SecondTurnLightsOn))
				GetWorldTimerManager().SetTimer(SecondTurnLightsOn,this, &AMoveTiffany::SecondTurnOn, .5f, false);
		});
		
		GetWorldTimerManager().SetTimer(FirstWait,WaitDelegate, .5f, false);
	}
}

void AMoveTiffany::SecondTurnOn()
{
	for (auto Element : OtherLights)
	{
		Element->TurnOn();
	}

	
	Player->SetPlayerOptions(false, true, true);
	OnFinishedEvent.Broadcast();
	Destroy();
}

//----------------
void AMoveTiffany::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AAlex>(OtherActor)) return;

	if(!bActionReady) return;
	if(DoOnce > 0) return;

	auto controller = Cast<AAlexPlayerController>(Player->GetController());
	controller->PlayRumbleFeedBack(1, 3, true, true, true, true);
	
	++DoOnce;
	OnStartEvent.Broadcast();

	Player->ForceLighterOff();
	Player->SetPlayerOptions(false, false, false);
	
	UGameplayStatics::SpawnSound2D(this, SFXHeartBeat);
	UGameplayStatics::SpawnSound2D(this, SFXTiffanyNear);
	
	FTimerDelegate FirstTurnOff;
	FirstTurnOff.BindLambda([&]
	{
		Tiffany->SetActorLocation(Target->GetActorLocation());
		Tiffany->SetActorRotation(Target->GetActorRotation());
		
		if (!GetWorldTimerManager().IsTimerActive(FirstTurnLightsOn))
		{
			GetWorldTimerManager().SetTimer(FirstTurnLightsOn, this, &AMoveTiffany::FirstTurnOn, .75f, false);
		}
		
	});

	for (auto Element : OtherLights)
	{
		Element->TurnOff();
	}
	
	if (!GetWorldTimerManager().IsTimerActive(FirstTurnLightsOff))
	{
		GetWorldTimerManager().SetTimer(FirstTurnLightsOff, FirstTurnOff, 2.f, false);
	}
}