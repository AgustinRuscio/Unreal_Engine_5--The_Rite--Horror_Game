//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "ChangingActor.h"

//----------------------------------------------------------------------------------------------------------------------
AChangingActor::AChangingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;
}

//----------------------------------------------------------------------------------------------------------------------
void AChangingActor::ChangeObjectMaterial(UMaterialInterface* NewMaterial) const
{
	MeshComponent->SetMaterial(0, NewMaterial);
}

//----------------------------------------------------------------------------------------------------------------------
void AChangingActor::ChangeObjectMesh(UStaticMesh* NewMesh) const
{
	MeshComponent->SetStaticMesh(NewMesh);
}

//----------------------------------------------------------------------------------------------------------------------
void AChangingActor::ChangeObjectVisuals(UMaterialInterface* NewMaterial, UStaticMesh* NewMesh) const
{
	if(NewMesh != nullptr)
		ChangeObjectMesh(NewMesh);
	
	if(NewMaterial != nullptr)
		ChangeObjectMaterial(NewMaterial);
}

//----------------------------------------------------------------------------------------------------------------------
void AChangingActor::ResetObjectVisuals()
{
	ChangeObjectMesh(OriginalMesh);
	
	ChangeObjectMaterial(OriginalMaterial);
}

//----------------------------------------------------------------------------------------------------------------------
void AChangingActor::BeginPlay()
{
	Super::BeginPlay();

	OriginalMesh = MeshComponent->GetStaticMesh();
	OriginalMaterial = MeshComponent->GetMaterial(0);
}