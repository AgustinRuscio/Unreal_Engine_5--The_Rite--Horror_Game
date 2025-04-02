//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "ClockLevelDrawersPuzzle.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Interactuables/SpectralObstacle.h"
#include "TheRite/Interactuables/SpectralWrittings.h"
#include "TheRite/Interactuables/Interactor.h"

//----------------------------------------------------------------------------------------------------------------------
AClockLevelDrawersPuzzle::AClockLevelDrawersPuzzle()
{
 	PrimaryActorTick.bCanEverTick = false;
}

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