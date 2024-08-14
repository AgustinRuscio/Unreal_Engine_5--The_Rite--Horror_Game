//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "HandLetter.h"

//*****************************Public******************************************
//******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AHandLetter::AHandLetter()
{
	PrimaryActorTick.bCanEverTick = true;

	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Letter Mesh");
}

//----------------------------------------------------------------------------------------------------------------------
void AHandLetter::SetLibraryMaterial() const
{
	LetterMesh->SetMaterial(0, LibraryMaterial);
}

//----------------------------------------------------------------------------------------------------------------------
void AHandLetter::SetOfficeMaterial() const
{
	LetterMesh->SetMaterial(0, OfficeMaterial);
}