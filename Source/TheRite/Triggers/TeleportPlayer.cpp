//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "TeleportPlayer.h"

#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
#include "TheRite/Characters/Alex.h"

//----------------------------------------------------------------------------------------------------------------------
ATeleportPlayer::ATeleportPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
}

//----------------------------------------------------------------------------------------------------------------------
void ATeleportPlayer::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATeleportPlayer::OnBeginOverlap);
}

//----------------------------------------------------------------------------------------------------------------------
void ATeleportPlayer::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AAlex* player = Cast<AAlex>(OtherActor))
	{
		player->SetActorLocation(TeleportLocation->GetActorLocation());

		if(bDestroyAfterUse)
			Destroy();
	}
}