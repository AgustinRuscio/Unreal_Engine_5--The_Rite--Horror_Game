//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "TheRite/Interactuables/Interactor.h"
#include "PressableButton.generated.h"

UCLASS()
class THERITE_API APressableButton : public AInteractor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	APressableButton();

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

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
	UPROPERTY(EditAnywhere, Category = "FeedBack")
	FVector LocationToAdd;
	
	FVector originalLocation;
	FVector endLocation;

	FTimeline ButtonTimeLine;

	UPROPERTY(EditDefaultsOnly, Category = "FeedBack")
	UCurveFloat* ButtonPressedCurveFloat;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds) override;

	UFUNCTION()
	void ButtonPressedTick(float deltaSeconds);
	UFUNCTION()
	void ButtonPressedFinished();
};