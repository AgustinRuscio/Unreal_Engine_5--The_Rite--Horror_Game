//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandLetter.generated.h"

UCLASS()
class THERITE_API AHandLetter : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* LetterMesh;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* OfficeMaterial;
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* LibraryMaterial;
	
public:
	AHandLetter();

	void SetLibraryMaterial();
	void SetOfficeMaterial();
};