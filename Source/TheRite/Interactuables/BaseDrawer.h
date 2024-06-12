//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "BaseDrawer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDrawerOpen, ABaseDrawer*, Drawer);

UCLASS()
class THERITE_API ABaseDrawer : public AInteractor
{
	GENERATED_BODY()

public:
	ABaseDrawer();

	bool IsOpen() const;
	bool IsKeyContainer() const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void Interaction() override;

	void SetKeyContainer();
	
	UFUNCTION()
	void AddingForce();

private:
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
		
public:	
	UPROPERTY(BlueprintAssignable, Category = "Drawer event")
	FOnDrawerOpen OnDrawerOpen;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float ForceIntensity;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveDir;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector ForceDir;

private:
	bool bKeyConteiner;
	bool bFlipFlop = true;
	bool bIsOpen = false;
	
	FVector StartLocation;
	FVector EndLocation;
	
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
};