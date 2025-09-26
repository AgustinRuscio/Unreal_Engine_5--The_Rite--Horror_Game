//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "InspectItem.h"

//----------------------------------------------------------------------------------------------------------------------
AInspectItem::AInspectItem()
{
 	PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

//----------------------------------------------------------------------------------------------------------------------
void AInspectItem::SetMesh(UStaticMesh* NewMesh)
{
	Mesh->SetStaticMesh(NewMesh);
}

//----------------------------------------------------------------------------------------------------------------------
void AInspectItem::MoveMesh(FVector2D vector)
{
}