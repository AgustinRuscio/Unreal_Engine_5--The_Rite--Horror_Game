//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Eye.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AEye::AEye()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMeshComponent;	
}

void AEye::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto GetTargetPosition = [&]()
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(),0);
	
		if(controller != nullptr)
			return controller->GetCharacter()->GetActorLocation();
		else
			return FVector::ZeroVector;
	};
	
	TargetPosition = GetTargetPosition();

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	
	NewRotation.Roll = 0;
	NewRotation.Pitch  = 0;
	
	SetActorRotation(NewRotation);
}