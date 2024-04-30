//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Altar.h"

#include "AltarWhell.h"

AAltar::AAltar()
{
 	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

void AAltar::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAltar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAltar::Interaction()
{
	if(!bIsFocus)
	{
		bIsFocus = true;
		//Hacer Focus
	}
	else
	{
		// Manejar los cambios
		Whells[WhellIndex]->Interaction();
	}
}

void AAltar::LeaveFocus()
{
	bIsFocus = false;
}
