//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "HandLetter.h"

AHandLetter::AHandLetter()
{
	PrimaryActorTick.bCanEverTick = true;

	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Letter Mesh");
	
}

void AHandLetter::SetLibraryMaterial()
{
	LetterMesh->SetMaterial(0, LibraryMaterial);
}

void AHandLetter::SetOfficeMaterial()
{
	LetterMesh->SetMaterial(0, OfficeMaterial);
}