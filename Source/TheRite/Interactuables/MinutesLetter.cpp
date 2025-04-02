//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "MinutesLetter.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
AMinutesLetter::AMinutesLetter()
{
 	PrimaryActorTick.bCanEverTick = false;

	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Letter mesh");
	RootComponent = LetterMesh;
}

//----------------------------------------------------------------------------------------------------------------------
void AMinutesLetter::Interaction()
{
	OnInteractionTrigger.Broadcast(this);
	OnAction.Broadcast();
	
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());
	Destroy();
}