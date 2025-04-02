//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "HourLetter.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
AHourLetter::AHourLetter()
{
 	PrimaryActorTick.bCanEverTick = false;

	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Letter mesh");
	RootComponent = LetterMesh;
}

//----------------------------------------------------------------------------------------------------------------------
void AHourLetter::Interaction()
{
	OnAction.Broadcast();
	OnInteractionTrigger.Broadcast(this);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());
	Destroy();
}