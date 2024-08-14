//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "ClockLevelDrawersPuzzle.h"

#include "TheRite/AlexPlayerController.h"
#include "TheRite/Interactuables/SpectralObstacle.h"
#include "TheRite/Interactuables/SpectralWrittings.h"
#include "TheRite/Interactuables/Interactor.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AClockLevelDrawersPuzzle::AClockLevelDrawersPuzzle()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AClockLevelDrawersPuzzle::BeginPlay()
{
	Super::BeginPlay();

	for (auto Element : KeySpectralWrittings)
	{
		Element->OnInteractionTrigger.AddDynamic(this, &AClockLevelDrawersPuzzle::OnKeySpectralWritingUsed);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AClockLevelDrawersPuzzle::OnKeySpectralWritingUsed(AInteractor* interactor)
{
	if(DestroyableSpectralIbstacle)
		DestroyableSpectralIbstacle->ObstacleDestroy();

	if(OtherSpectralWrittings.Num() == 0) return;
	
	for (auto writtings : OtherSpectralWrittings)
	{
		writtings->Discovered();
	}

	auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->PlayRumbleFeedBack(1, 5, true, true, true, true);
	
	Destroy();
}