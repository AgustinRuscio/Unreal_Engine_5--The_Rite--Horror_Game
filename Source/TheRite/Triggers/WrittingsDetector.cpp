//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "WrittingsDetector.h"
#include "Components/SphereComponent.h"
#include "TheRite/Components/FadeObjectComponent.h"
#include "TheRite/Components/Fader.h"
#include "TheRite/Interactuables/SpectralWrittings.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AWrittingsDetector::AWrittingsDetector()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	TriggerDetector = CreateDefaultSubobject<USphereComponent>("TriggerDetector");
	
	TriggerDetector->OnComponentBeginOverlap.AddDynamic(this, &AWrittingsDetector::OnOverlapBegins);
	TriggerDetector->OnComponentEndOverlap.AddDynamic(this, &AWrittingsDetector::OnOverlapEnds);
	
	TriggerDetector->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//----------------------------------------------------------------------------------------------------------------------
void AWrittingsDetector::SetComponentSettings(float radius, FTransform transform)
{
	SetRadius(Radius);
	SetLocation(transform);
}

//----------------------------------------------------------------------------------------------------------------------
void AWrittingsDetector::SetInteractionStatus(bool newStatus)
{
	bInteracionOn = newStatus;
	
	if(bInteracionOn)
		TriggerDetector->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	else
	{
		TriggerDetector->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		//if( !currentWritting) return;
		if(OverlappedFadeObjects.Num() == 0) return;

		for (auto Element : OverlappedFadeObjects)
		{
			Element->OnFadeDeActivate();
		}
		
		OverlappedFadeObjects.Empty();
		
		//currentWritting->Deactivate();
		//currentWritting = nullptr;
	}
}

//*****************************Private*********************************************
//********************************************************************************

//-----------------------------------------------------------------------------------------------------------------------
void AWrittingsDetector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if(OverlappedFadeObjects.Num() > 0)
	//{
	//	for (auto Element : OverlappedFadeObjects)
	//	{
	//		float DistanceToCenter = FVector::Dist(Element->GetActor()->GetActorLocation(), GetActorLocation());
	//
	//		float NormalizedDistance = FMath::Clamp(DistanceToCenter/TriggerDetector->GetScaledSphereRadius(), 0.f, 1.f);
	//
	//		float AlphaValue = FMath::Lerp(1.f, 0.f, NormalizedDistance);
	//		Element->SetAlpha(AlphaValue);
	//	}
	//}
	
	ChangeCurrentWritingAlpha();
}

//-----------------------------------------------------------------------------------------------------------------------
#pragma region Setter Methods
void AWrittingsDetector::ChangeCurrentWritingAlpha()
{
	if(OverlappedFadeObjects.Num() == 0) return;
	
	for (auto Element : OverlappedFadeObjects)
	{
		if(Element == nullptr) continue;
		
		float DistanceToCenter = FVector::Dist(Element->GetActor()->GetActorLocation(), GetActorLocation());
	
		float NormalizedDistance = FMath::Clamp(DistanceToCenter/TriggerDetector->GetScaledSphereRadius(), 0.f, 1.f);
	
		float AlphaValue = FMath::Lerp(1.f, 0.f, NormalizedDistance);
		Element->SetAlpha(AlphaValue);
	}
	
	//if(!bwrittingDetected || currentWritting == nullptr) return;
//
	//float DistanceToCenter = FVector::Dist(currentWritting->GetActorLocation(), GetActorLocation());
	//
	//float NormalizedDistance = FMath::Clamp(DistanceToCenter/TriggerDetector->GetScaledSphereRadius(), 0.f, 1.f);
	//
	//float AlphaValue = FMath::Lerp(1.f, 0.f, NormalizedDistance);
	//
	//currentWritting->SetMaterialAlpha(AlphaValue);
}

//-----------------------------------------------------------------------------------------------------------------------
void AWrittingsDetector::SetRadius(float newRadius)
{
	TriggerDetector->SetSphereRadius(newRadius);
}

//-----------------------------------------------------------------------------------------------------------------------
void AWrittingsDetector::SetLocation(FTransform newLocation)
{
	TriggerDetector->SetRelativeTransform(newLocation);
}
#pragma endregion 

//-----------------------------------------------------------------------------------------------------------------------
#pragma region Collision Methods
void AWrittingsDetector::OnOverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto castedComponent = Cast<IFader>(OtherActor);
	
	if(!castedComponent) return;

	if(!OverlappedFadeObjects.Contains(castedComponent))
		OverlappedFadeObjects.Add(castedComponent);

	castedComponent->OnFadeActivate();


	//auto castedActor = Cast<ASpectralWrittings>(OtherActor);
	//if(!castedActor) return;

	//currentWritting = castedActor;

	//bwrittingDetected = true;
	//currentWritting->Activate();
}

//-----------------------------------------------------------------------------------------------------------------------
void AWrittingsDetector::OnOverlapEnds(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto castedComponent = Cast<IFader>(OtherActor);

	if(!castedComponent) return;
	
	if(!OverlappedFadeObjects.Contains(castedComponent)) return;
		
	castedComponent->OnFadeDeActivate();
	OverlappedFadeObjects.Remove(castedComponent);
	
	
	//auto castedActor = Cast<ASpectralWrittings>(OtherActor);
	//if(!castedActor) return;
	//if(castedActor != currentWritting) return;
	//
	//currentWritting->Deactivate();
	//currentWritting = nullptr;
	//bwrittingDetected = false;
}
#pragma endregion