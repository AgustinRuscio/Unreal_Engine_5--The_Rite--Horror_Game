//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Interactor.h"
#include "AltarWhell.generated.h"

class AStatuette;

UCLASS()
class THERITE_API AAltarWhell : public AInteractor
{
 	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AAltarWhell();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	bool CheckRotation();

	virtual void Interaction() override;
	
	void EnableInteraction();
	void DisableInteraction();
	void StatuetteReady();

	void ASignValues(AStatuette* Statuette, float DesiredRotation, float RotationToAdd);
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	float DesiredRotation;
	float RotationToAdd;

	bool bStatuette;
	
	FRotator InteractionRotator;
	FRotator StatuateRotator;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category= "SFX")
	USoundBase* SFX_Rotation;
	
	FTimeline MoveTimeLine;

	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UCurveFloat* CurveFloat;
	
	AStatuette* Statuette;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void BindTimeLines();
	
	UFUNCTION()
	void MoveTimeLineTick(float deltaSeconds);
	
	UFUNCTION()
	void MoveTimeLineFinished();
};