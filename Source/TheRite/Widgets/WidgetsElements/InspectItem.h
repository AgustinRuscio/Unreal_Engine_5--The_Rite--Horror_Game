//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InspectItem.generated.h"

UCLASS()
class THERITE_API AInspectItem : public AActor
{
	GENERATED_BODY()
	
public:	
	//CONSTRUCTOR & COMPONENTS
	AInspectItem();

	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void SetMesh(UStaticMesh* NewMesh);

	void MoveMesh(FVector2D vector, float speed);

private:
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
};