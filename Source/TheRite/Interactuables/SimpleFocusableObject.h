//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
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

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	virtual void Interaction() override;

protected:
	//*****************************************************************************//
	//								PROTECTED VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<class UCommonActivatableWidget> DisplayedWidgetBase;

	class UCommonActivatableWidget* DisplatedWidget;

	//*****************************************************************************//
	//								PROTECTED METHODS							   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

		UFUNCTION()
	void LeaveFocus();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bShowDefaultWidgets = true;
	bool bIsFocus;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FRotator ExittingRotation;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector ExittingVector;

	class AAlex* Player;
};