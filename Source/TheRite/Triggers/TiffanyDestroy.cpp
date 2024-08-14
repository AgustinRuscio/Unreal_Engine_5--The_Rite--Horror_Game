//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "TiffanyDestroy.h"
#include "TheRite/Characters/Tiffany.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "Components/BoxComponent.h"
#include "TheRite/Characters/Alex.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ATiffanyDestroy::ATiffanyDestroy()
{
 	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box collision");
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ATiffanyDestroy::OnOverlapBegin);
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ATiffanyDestroy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AAlex>(OtherActor)) return;

	NearLight->TurnOff();
	
	if (!GetWorldTimerManager().IsTimerActive(FirstTimer))
	{
		FTimerDelegate Delegate;
		Delegate.BindLambda([&]
		{
			TiffanyToDestroy->Destroy();
	
			if (!GetWorldTimerManager().IsTimerActive(SecondsTimer))
			{
				FTimerDelegate SecondDelegate;
				SecondDelegate.BindLambda([&]
				{
					NearLight->TurnOn();
					Destroy();
				});
				
				GetWorldTimerManager().SetTimer(SecondsTimer, SecondDelegate, 1.0f, false);
			}
		});
		
		GetWorldTimerManager().SetTimer(FirstTimer, Delegate, 1.2f, false);
	}
}