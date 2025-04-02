//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandLetter.generated.h"

UCLASS()
class THERITE_API AHandLetter : public AActor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	AHandLetter();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void SetLibraryMaterial() const;
	void SetOfficeMaterial() const;
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* LetterMesh;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* OfficeMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* LibraryMaterial;
};