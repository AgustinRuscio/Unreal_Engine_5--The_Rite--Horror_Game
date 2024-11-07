//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "WalkerTiffany.h"

#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Characters/Tiffany.h"

//----------------------------------------------------------------------------------------------------------------------
AWalkerTiffany::AWalkerTiffany() : bDoOnce(false)
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWalkerTiffany::OnOverlapBegin);
}

//----------------------------------------------------------------------------------------------------------------------
void AWalkerTiffany::BeginPlay()
{
	Super::BeginPlay();

	if(WalkerTiffany)
	{
		WalkerTiffany->SetActorLocation(SpawnTargetPoint->GetActorLocation());
		WalkerTiffany->SetActorRotation(SpawnTargetPoint->GetActorRotation());
		WalkerTiffany->SetData(true, false, true);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("No tifany seted")));
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AWalkerTiffany::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AAlex>(OtherActor) || bDoOnce || !bReadyToWalk) return;

	bDoOnce = true;
	WalkerTiffany->StartMovement(DesiredTargetPoint);
	Destroy();
}