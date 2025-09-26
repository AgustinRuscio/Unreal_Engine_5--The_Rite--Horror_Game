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
	Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	RootComponent = Mesh;
}

//----------------------------------------------------------------------------------------------------------------------
void AInspectItem::SetMesh(UStaticMesh* NewMesh)
{
	Mesh->SetStaticMesh(NewMesh);
}

//----------------------------------------------------------------------------------------------------------------------
void AInspectItem::MoveMesh(const FVector2D& vector, float speed)
{
	MyYaw	+= vector.X * speed;
	MyPitch += vector.Y * speed;

	FRotator NewRotation = FRotator(MyPitch, MyYaw, 0.f);

	SetActorRotation(NewRotation);
}

//----------------------------------------------------------------------------------------------------------------------
void AInspectItem::BeginPlay()
{
	Super::BeginPlay();
	
	MyYaw = GetActorRotation().Yaw;
	MyPitch = GetActorRotation().Pitch;
}