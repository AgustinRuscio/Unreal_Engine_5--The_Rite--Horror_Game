//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "RotateComponent.h"

//----------------------------------------------------------------------------------------------------------------------
URotateComponent::URotateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void URotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetOwner()->AddActorLocalRotation(RotateVector);
}