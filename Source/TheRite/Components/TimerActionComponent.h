//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerActionComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerBroadcast);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERITE_API UTimerActionComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	UTimerActionComponent();
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnTimerBroadcast TimerReach;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	void ActionFinished();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	float Timer = 0;

	UPROPERTY(EditAnywhere, Category = "Timer States")
	float CD = 0;

	bool bShowLighterOff = true;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void RunTimer(float deltaTime);
};