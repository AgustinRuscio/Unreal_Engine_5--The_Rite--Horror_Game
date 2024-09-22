//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "SimonButton.h"
#include "Components/PointLightComponent.h"

static float PressedLocation;
static float NormalLocation;

//----------------------------------------------------------------------------------------------------------------------
ASimonButton::ASimonButton()
{
 	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	RootComponent = MeshComponent;

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("Point Light Component");
	PointLightComponent->SetupAttachment(MeshComponent);

	//Set Light settings
	PointLightComponent->SetAttenuationRadius(6.f);
	PointLightComponent->SetIntensity(0.f);
	PointLightComponent->SetLightColor(SetPointLightColor());
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::Interaction()
{
	if(!bCanInteract) return;

	OnInteractionStart.Broadcast(static_cast<int8>(Color));
	
	bCanInteract = false;
	InteractionTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::Deactivate()
{
	Super::Deactivate();
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::PressForced()
{
	InteractionTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
FLinearColor ASimonButton::SetPointLightColor() const
{
	switch (Color)
	{
	case EButtonColor::Red:
		return FLinearColor::Red;
			
	case EButtonColor::Yellow:
		return FLinearColor::Yellow;
			
	case EButtonColor::Blue:
		return FLinearColor::Blue;
			
	case EButtonColor::Green:
		return FLinearColor::Green;
	}
	
	return FLinearColor::White;
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::BeginPlay()
{
	Super::BeginPlay();

	NormalLocation	= GetActorLocation().Z;
	PressedLocation = GetActorLocation().Z - 0.4f;
	
	BindTimeLineMethods();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InteractionTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::BindTimeLineMethods()
{
	FOnTimelineFloat InteractionTick;
	InteractionTick.BindUFunction(this, FName("InteractionTick"));
	InteractionTimeLine.AddInterpFloat(InteractionCurveFloat, InteractionTick);
	
	FOnTimelineEventStatic InteractionFinished;
	InteractionFinished.BindUFunction(this, FName("InteractionFinished"));
	InteractionTimeLine.SetTimelineFinishedFunc(InteractionFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::InteractionTick(float deltaSeconds)
{
	PointLightComponent->SetIntensity(deltaSeconds);
	auto newZ = FMath::Lerp(NormalLocation, PressedLocation, deltaSeconds);

	auto NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y, newZ);
	SetActorLocation(NewLocation);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::InteractionFinished()
{
	bCanInteract = true;
	OnInteractionFinished.Broadcast();
}