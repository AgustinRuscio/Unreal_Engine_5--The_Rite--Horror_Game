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
	
private:
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
	
	

	bool bKeyConteiner;
	bool bFlipFlop = true;
	bool bIsOpen = false;


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

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveDir;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector ForceDir;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ForceIntensity;
	
public:	
	ABaseDrawer();

	bool IsOpen() const;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintAssignable, Category = "Drawer event")
	FOnDrawerOpen OnDrawerOpen;
	
	virtual void Interaction() override;

	bool IsKeyContainer() const;
	void SetKeyContainer();
	
	UFUNCTION()
	void AddingForce();
};