//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "DoorScaryKnocking.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Door.h"

//----------------------------------------------------------------------------------------------------------------------
ADoorScaryKnocking::ADoorScaryKnocking()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoorScaryKnocking::OnOverlapBegin);
}

//----------------------------------------------------------------------------------------------------------------------
void ADoorScaryKnocking::Activate()
{
	bActive = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ADoorScaryKnocking::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bActive || !Cast<AAlex>(OtherActor) || bDoOnce) return;

	bDoOnce = true;

	for (auto Element : Doors)
	{
		Element->ScaryKnock();
	}

	for (int i = 0; i < SFX.Num(); i++)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SFX[i], Doors[i]->GetActorLocation());
	}
	OnTriggerActivatedDelegate.Broadcast();
	Destroy();
}