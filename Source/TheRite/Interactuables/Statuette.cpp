#include "Statuette.h"

AStatuette::AStatuette()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void AStatuette::BeginPlay()
{
	Super::BeginPlay();
	
}


void AStatuette::Interaction()
{
	Super::Interaction();

	Destroy();
}
