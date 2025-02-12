//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "SimonButton.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
ASimonButton::ASimonButton()
{
 	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	RootComponent = MeshComponent;

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("Point Light Component");
	PointLightComponent->SetupAttachment(MeshComponent);

	//Set Light settings
	PointLightComponent->SetAttenuationRadius(10.f);
	PointLightComponent->SetIntensity(0.f);
	PointLightComponent->SetIntensityUnits(ELightUnits::Lumens);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::Interaction()
{
	if(!bCanInteract) return;

	OnInteractionStart.Broadcast(Color);
	
	bCanInteract = false;
	PlayInteractionFeedBack();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::Activate()
{
	Super::Activate();
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
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
	PlayInteractionFeedBack();
}

//----------------------------------------------------------------------------------------------------------------------
FLinearColor ASimonButton::SetPointLightColor() const
{
	switch (Color)
	{
	case 0:
		return FLinearColor::Red;
			
	case 1:
		return FLinearColor::Yellow;
			
	case 2:
		return FLinearColor::Blue;
			
	case 3:
		return FLinearColor::Green;
	}
	
	return FLinearColor::White;
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::BeginPlay()
{
	Super::BeginPlay();

	NormalLocation	= GetActorLocation();
	PressedLocation = GetActorLocation() - LocationToSubtract;
	
	BindTimeLineMethods();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InteractionTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::PlayInteractionFeedBack()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PressedSounds, GetActorLocation());
	InteractionTimeLine.PlayFromStart();
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
	auto newLocation = FMath::Lerp(NormalLocation, PressedLocation, deltaSeconds);

	SetActorLocation(newLocation);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimonButton::InteractionFinished()
{
	bCanInteract = true;
	OnInteractionFinished.Broadcast();
}