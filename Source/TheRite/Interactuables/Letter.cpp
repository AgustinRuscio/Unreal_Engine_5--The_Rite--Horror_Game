//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Letter.h"

#include "Kismet/GameplayStatics.h"

//*****************************Public***********************************************
//***********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ALetter::ALetter()
{
 	PrimaryActorTick.bCanEverTick = true;
	
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