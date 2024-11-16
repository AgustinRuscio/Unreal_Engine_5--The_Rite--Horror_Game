//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChangingActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegateChanged, UMaterialInterface*, NewMaterial, UStaticMesh*, NewMesh);

UCLASS()
class THERITE_API AChangingActor : public AActor
{
	GENERATED_BODY()

	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AChangingActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Visuals, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	
	void ChangeObjectMaterial(UMaterialInterface* NewMaterial) const;

	void ChangeObjectMesh(UStaticMesh* NewMesh) const;

	void ChangeObjectVisuals(UMaterialInterface* NewMaterial, UStaticMesh* NewMesh) const;

	void ResetObjectVisuals();
	
private:
	
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UStaticMesh* OriginalMesh;
	UMaterialInterface* OriginalMaterial;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//

	virtual void BeginPlay() override;
};