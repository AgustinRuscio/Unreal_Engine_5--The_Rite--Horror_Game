//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "Letter.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
ALetter::ALetter()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Letter mesh");
}

//----------------------------------------------------------------------------------------------------------------------
void ALetter::Interaction()	
{
	OnInteractionTrigger.Broadcast(this);
	OnAction.Broadcast();
	
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());
	Destroy();
}