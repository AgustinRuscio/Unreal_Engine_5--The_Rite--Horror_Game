//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "TheRite/Interactuables/Interactor.h"
#include "BaseDrawer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDrawerOpen, ABaseDrawer*, Drawer);

UCLASS()
class THERITE_API ABaseDrawer : public AInteractor
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ABaseDrawer();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(BlueprintAssignable, Category = "Drawer event")
	FOnDrawerOpen OnDrawerOpen;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	bool IsOpen() const;
	bool IsKeyContainer() const;
	
	virtual void Interaction() override;

	void SetKeyContainer();
	
	UFUNCTION()
	void AddingForce();

protected:
	//*****************************************************************************//
	//								PRTOTECTED VARIABLES						   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Movement")
	float ForceIntensity;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveDir;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector ForceDir;

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bKeyConteiner;
	bool bFlipFlop = true;
	bool bIsOpen = false;
	
	FVector StartLocation;
	FVector EndLocation;
	
	UPROPERTY(EditAnywhere, Category="Mesh")
	USoundBase* OpenSound;

	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* DrawerModel;

	UPROPERTY()
	FTimeline OpenTimeLine;
	
	UPROPERTY()
	FTimeline CloseTimeLine;
	
	UPROPERTY()
	FTimeline WaitTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* BothTimeLineCurve;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void BindTimeLines();
	
	UFUNCTION()
	void OpenTimeLineUpdate(float value);
	
	UFUNCTION()
	void CloseTimeLineUpdate(float value);
	
	UFUNCTION()
	void WaitTimeLineUpdate(float value);
	
	UFUNCTION()
	void TimelineFinished();
	
	UFUNCTION()
	void WaitTimelineFinished();
};