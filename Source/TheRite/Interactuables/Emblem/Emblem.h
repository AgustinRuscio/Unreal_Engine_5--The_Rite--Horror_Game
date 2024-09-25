//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Emblem.generated.h"

UCLASS()
class THERITE_API AEmblem : public AInteractor
{
	GENERATED_BODY()

public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AEmblem();

	UPROPERTY(EditDefaultsOnly, Category = Visuals, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	virtual void Interaction() override;

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
};