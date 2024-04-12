
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerActionComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerBroadcast);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERITE_API UTimerActionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	float Timer = 0;
	UPROPERTY(EditAnywhere, Category = "Timer States")
	float CD = 0;
	
	bool bShowLighterOff = true;

	void RunTimer(float deltaTime);
	
protected:
	virtual void BeginPlay() override;

public:	
	UTimerActionComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnTimerBroadcast TimerReach;
	void ActionFinished();
};