#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "FloatingActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERITE_API UFloatingActorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category= "Settings", meta=(ToolTip = "If true movement will start on begin play"))
	bool bAutoStart = true;

	UPROPERTY(EditAnywhere, Category= "Settings", meta=(ToolTip = "If true movement will loop"))
	bool bLoop = true;
	
	UPROPERTY(EditAnywhere, Category= "Settings", meta=(ToolTip = "If true, the movement will wait x seconds before moving again"))
	bool bWillWait;

	UPROPERTY(EditAnywhere, Category= "Settings", meta=(ToolTip = "Time to be wait  until movemevent start again. Only used if loop = true"))
	float WaitTime;
	
	bool bFlipFlop = true;

	FTimeline MovingTimeLine;
	FTimerHandle WaitingHandler;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UCurveFloat* TimeLineCurve;

	void BindTimeLine();
	
	UFUNCTION()
	void OnMovementTick(float deltaTime);
	UFUNCTION()
	void OnMovementFinished();

	FVector StartLocation;
	FVector EndLocation;

	UPROPERTY(EditAnywhere, Category= "Settings", meta=(ToolTip = "This vector will sum to the initial position, resulting on the end position to be reached"))
	FVector AddingVector;

	AActor* MyOwnerActor;
	
protected:
	virtual void BeginPlay() override;

public:	
	UFloatingActorComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Activate();
	void Stop();
};