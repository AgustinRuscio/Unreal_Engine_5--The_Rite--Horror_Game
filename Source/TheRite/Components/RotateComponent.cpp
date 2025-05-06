//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "RotateComponent.h"
#include "Math/Rotator.h"

namespace 
{
	float CurrentRotation;
	float TotalRotation;
}

//----------------------------------------------------------------------------------------------------------------------
URotateComponent::URotateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//----------------------------------------------------------------------------------------------------------------------
void URotateComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialRotator = GetOwner()->GetActorRotation();
	FinalRotator = InitialRotator + RotateVector;
	AccumulatedRotation = FRotator::ZeroRotator;
}

//----------------------------------------------------------------------------------------------------------------------
void URotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Aplicamos rotación
	GetOwner()->AddActorLocalRotation(RotateVector * DeltaTime);

	// Acumulamos cuánto rotamos
	AccumulatedRotation += RotateVector * DeltaTime;

	if (!bShouldLoopBack) return;

	// Comprobamos si superamos la rotación deseada en todos los ejes
	bool bXReached = FMath::Abs(AccumulatedRotation.Pitch) >= FMath::Abs(RotateVector.Pitch);
	bool bYReached = FMath::Abs(AccumulatedRotation.Yaw) >= FMath::Abs(RotateVector.Yaw);
	bool bZReached = FMath::Abs(AccumulatedRotation.Roll) >= FMath::Abs(RotateVector.Roll);

	// Solo invertimos cuando en todos los ejes activos alcanzamos la rotación deseada
	if (
		(bXReached || FMath::IsNearlyZero(RotateVector.Pitch)) &&
		(bYReached || FMath::IsNearlyZero(RotateVector.Yaw)) &&
		(bZReached || FMath::IsNearlyZero(RotateVector.Roll))
		)
	{
		RotateVector *= -1.f;
		AccumulatedRotation = FRotator::ZeroRotator;
	}
}
