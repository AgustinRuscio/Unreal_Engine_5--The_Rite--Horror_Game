//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "FloatingActorComponent.h"
#include "GameFramework/Actor.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
UFloatingActorComponent::UFloatingActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void UFloatingActorComponent::ActivateComponent()
{
	MovingTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void UFloatingActorComponent::StopComponent()
{
	MovingTimeLine.Stop();
}

//*****************************Private********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void UFloatingActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	BindTimeLine();

	MyOwnerActor = GetOwner();
	
	StartLocation = MyOwnerActor->GetActorLocation();
	EndLocation = StartLocation + AddingVector;
	
	if(bAutoStart)
		MovingTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void UFloatingActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	MovingTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
# pragma region TimeLine Methods
void UFloatingActorComponent::BindTimeLine()
{
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("OnMovementTick"));
	MovingTimeLine.AddInterpFloat(TimeLineCurve, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("OnMovementFinished"));
	MovingTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void UFloatingActorComponent::OnMovementTick(float deltaTime)
{
	auto lerpingValue = FMath::Lerp(StartLocation, EndLocation, deltaTime);

	MyOwnerActor->SetActorLocation(lerpingValue);
}

//----------------------------------------------------------------------------------------------------------------------
void UFloatingActorComponent::OnMovementFinished()
{
	if(bLoop)
	{
		if(bFlipFlop)
		{
			if(bWillWait)
			{
				if (!MyOwnerActor->GetWorldTimerManager().IsTimerActive(WaitingHandler))
				{
					FTimerDelegate timerDelegate;
					timerDelegate.BindLambda([&]
					{
						bFlipFlop = false;
						MovingTimeLine.ReverseFromEnd();
					});
		
					MyOwnerActor->GetWorldTimerManager().SetTimer(WaitingHandler, timerDelegate, WaitTime, false);
				}
			}
			else
			{
				bFlipFlop = false;
				MovingTimeLine.ReverseFromEnd();
			}
		}
		else
		{
			if(bWillWait)
			{
				if (!MyOwnerActor->GetWorldTimerManager().IsTimerActive(WaitingHandler))
				{
					FTimerDelegate timerDelegate;
					timerDelegate.BindLambda([&]
					{
						bFlipFlop = true;
						MovingTimeLine.PlayFromStart();
					});
		
					MyOwnerActor->GetWorldTimerManager().SetTimer(WaitingHandler, timerDelegate, WaitTime, false);
				}
			}
			else
			{
				bFlipFlop = true;
				MovingTimeLine.PlayFromStart();
			}
		}
	}
}
#pragma endregion 