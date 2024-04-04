//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "WrittingsDetector.h"

AWrittingsDetector::AWrittingsDetector()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	TriggerDetector = CreateDefaultSubobject<USphereComponent>("TriggerDetector");
	
	TriggerDetector->OnComponentBeginOverlap.AddDynamic(this, &AWrittingsDetector::OnOverlapBegins);
	TriggerDetector->OnComponentEndOverlap.AddDynamic(this, &AWrittingsDetector::OnOverlapEnds);
	
	TriggerDetector->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWrittingsDetector::OnOverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto castedActor = Cast<ASpectralWrittings>(OtherActor);
	
	if(!castedActor) return;

	currentWritting = castedActor;
	UE_LOG(LogTemp, Warning, TEXT("Active"));
	bwrittingDetected = true;
	currentWritting->Activate();
}

void AWrittingsDetector::OnOverlapEnds(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto castedActor = Cast<ASpectralWrittings>(OtherActor);
	if(!castedActor) return;
	if(castedActor != currentWritting) return;
	
	currentWritting->Deactivate();
	currentWritting = nullptr;
	bwrittingDetected = false;
}

void AWrittingsDetector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bwrittingDetected || currentWritting == nullptr) return;

	float DistanceToCenter = FVector::Dist(currentWritting->GetActorLocation(), GetActorLocation());
	
	float NormalizedDistance = FMath::Clamp(DistanceToCenter/TriggerDetector->GetScaledSphereRadius(), 0.f, 1.f);
	
	float AlphaValue = FMath::Lerp(1.f, 0.f, NormalizedDistance);
	
	currentWritting->SetMaterialAlpha(AlphaValue);
}

void AWrittingsDetector::SetInteractionStatus(bool newStatus)
{
	bInteracionOn = newStatus;

	
	if(bInteracionOn)
		TriggerDetector->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	else
	{
		TriggerDetector->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		if( !currentWritting) return;
		
		currentWritting->Deactivate();
		currentWritting = nullptr;
	}
}

void AWrittingsDetector::SetComponentSettings(float radius, FTransform transform)
{
	SetRadius(radius);
	SetLocation(transform);
}

void AWrittingsDetector::SetRadius(float newRadius)
{
	TriggerDetector->SetSphereRadius(newRadius);
}

void AWrittingsDetector::SetLocation(FTransform newLocation)
{
	TriggerDetector->SetRelativeTransform(newLocation);
}