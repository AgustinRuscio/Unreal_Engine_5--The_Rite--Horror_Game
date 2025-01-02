//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "TheRite/Interactuables/Interactor.h"
#include "GameFramework/Actor.h"
#include "SimpleFocusableObject.generated.h"

UCLASS()
class THERITE_API ASimpleFocusableObject : public AInteractor
{
	GENERATED_BODY()

public:

	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ASimpleFocusableObject();

	UPROPERTY(EditDefaultsOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ObjectMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* CameraLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* PlayerLocationComp;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

public:	
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bIsFocus;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FRotator ExittingRotation;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector ExittingVector;

	class AAlex* Player;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	virtual void Interaction() override;

	UFUNCTION()
	void LeaveFocus();
};