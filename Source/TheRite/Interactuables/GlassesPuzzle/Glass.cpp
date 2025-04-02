//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "Glass.h"
#include "TheRite/LevelsGameFlow/Hospital/GlassesTablePuzzle.h"

//----------------------------------------------------------------------------------------------------------------------
AGlass::AGlass()
{
	PrimaryActorTick.bCanEverTick = false;

	GlassMesh = CreateDefaultSubobject<UStaticMeshComponent>("Glass Mesh");
	RootComponent = GlassMesh;
}

//----------------------------------------------------------------------------------------------------------------------
void AGlass::Interaction()
{
	OnInteractionTrigger.Broadcast(this);

	TablePuzzle->ObtainGlass();
	Destroy();
}