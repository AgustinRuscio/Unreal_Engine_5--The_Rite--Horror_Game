//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "CloseDoor.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Characters/Alex.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ACloseDoor::ACloseDoor()
{
 	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACloseDoor::OnOverlapBegin);
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ACloseDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AAlex>(OtherActor)) return;

	Door->HardClosing();

	if(bWillLockTheDoor)
		Door->SetLockedState(true);

	for (auto Element : Lights)
	{
		bAggresiveLight ? Element->SetAggressiveMaterial() : Element->SetNormalMaterial();
	}
	
	if(IsValid(DestroyableLight))
	{
		DestroyableLight->Destroy();
		UGameplayStatics::PlaySound2D(this, SFXLightBReak);
	}
	
	Destroy();
}