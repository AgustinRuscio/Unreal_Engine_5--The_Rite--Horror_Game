//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "TriggererObject.h"

#include "Components/BoxComponent.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Triggers/ObjectTriggerer.h"

//----------------------------------------------------------------------------------------------------------------------
ATriggererObject::ATriggererObject()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	RootComponent = Trigger;
}

//----------------------------------------------------------------------------------------------------------------------
bool ATriggererObject::ActiveState() const
{
	return bActive;
}

//----------------------------------------------------------------------------------------------------------------------
void ATriggererObject::Activate()
{
	bActive = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ATriggererObject::Deactivate()
{
	bActive = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ATriggererObject::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATriggererObject::OnTriggerBegin);
}

//----------------------------------------------------------------------------------------------------------------------
void ATriggererObject::OnTriggerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bActive) return;
	
	if(!Cast<AAlex>(OtherActor)) return;
	
	OnTriggererObjectEvent.Broadcast();
	
	for (auto Element : TriggererObjects)
	{
		Element->Trigger();
	}
	
	Destroy();
}