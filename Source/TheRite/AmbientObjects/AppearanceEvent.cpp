//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "AppearanceEvent.h"

#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"

//----------------------------------------------------------------------------------------------------------------------
AAppearanceEvent::AAppearanceEvent()
{
	PrimaryActorTick.bCanEverTick = true;
	bVisible					  = false;
	DistanceWithPlayer			  = 0.0f;

	 SkeletalMesh= CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	
	SkeletalMesh->SetupAttachment(RootComponent);
	StaticMesh->SetupAttachment(RootComponent);
}

//----------------------------------------------------------------------------------------------------------------------
void AAppearanceEvent::MakeAppear()
{
	OnAppearanceEventStart.Broadcast();
	bVisible = true;

	ChangeMeshesVisibility(bVisible);
}

//----------------------------------------------------------------------------------------------------------------------
void AAppearanceEvent::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AAlex>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	ChangeMeshesVisibility(false);
}

//----------------------------------------------------------------------------------------------------------------------
void AAppearanceEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateDistance(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void AAppearanceEvent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(GetWorld())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);

		TimerDelegate.Unbind();
	}

	Player = nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
void AAppearanceEvent::ChangeMeshesVisibility(bool visibility)
{
	SkeletalMesh->SetVisibility(visibility);
	StaticMesh->SetVisibility(visibility);
}

//----------------------------------------------------------------------------------------------------------------------
void AAppearanceEvent::MakeDisappear()
{
	OnAppearanceEventEndStart.Broadcast();
	UGameplayStatics::PlaySound2D(GetWorld(), Sound);
	

	if(!GetWorldTimerManager().IsTimerActive(TimerHandle))
	{
		TimerDelegate.BindLambda([&]
		{
			ChangeMeshesVisibility(false);
			OnAppearanceEventEndEnd.Broadcast();
		});
		
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TimeForSecondCallback, false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AAppearanceEvent::CalculateDistance(float DeltaSecond)
{
	if(!bVisible) return;

	float distance = FVector::Distance(Player->GetActorLocation(), GetActorLocation());

	
	UE_LOG(LogTemp, Display, TEXT("Distance is %f"), distance);

	if(WasRecentlyRendered(.001f) && distance <= DistanceWithPlayer)
	{
		if(TimeToSee <= counter)
		{
			bVisible = false;
			counter = 0;
			MakeDisappear();
		}
		else
		{
			counter += DeltaSecond;
		}
	}
	
}