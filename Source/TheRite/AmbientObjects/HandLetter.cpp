//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "HandLetter.h"

//*****************************Public******************************************
//******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AHandLetter::AHandLetter()
{
	PrimaryActorTick.bCanEverTick = false;

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