//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Tiffany.h"

#include "Components/AudioComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TheRite/AI/TiffanyController.h"
#include "AIController.h"
#include "Components/SphereComponent.h"
#include "Engine/TargetPoint.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"

ATiffany::ATiffany()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->InitSphereRadius(305.0f);
	Sphere->SetupAttachment(GetMesh());
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ATiffany::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ATiffany::OnOverlapEnd);

	GetMesh()->SetMobility(EComponentMobility::Movable);
	
	CryingAudio = CreateDefaultSubobject<UAudioComponent>("Crying");
}

//---------------- States Methods
bool ATiffany::GetWalkingState() const
{
	return bWalking;
}

bool ATiffany::SetHasToMove(bool hasToMoveState)
{
	return bHasToMove;
}

//---------------- System Methods
void ATiffany::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATiffany::BeginPlay()
{
	Super::BeginPlay();
	auto AIController = CastChecked<ATiffanyController>(GetController());
	
	BlackBoard = AIController->GetBlackboardComponent();
}

//---------------- Movement Methods
void ATiffany::StartMovement(ATargetPoint* newTarget)
{
	bWalking = true;
	
	BlackBoard->SetValueAsObject(TargetKey, newTarget);
	BlackBoard->SetValueAsBool(BooleanKey, true);
}

void ATiffany::SetData(bool IsVisible, bool NoCollision, bool HasToMove)
{
	GetMesh()->SetVisibility(IsVisible);

	if(NoCollision)
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bHasToMove = HasToMove;
}

void ATiffany::SetWaypoints(TArray<ATargetPoint*> targets)
{
	Waypoints = targets;
}

//---------------- Collider Methods
void ATiffany::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(static_cast<EObjectTypeQuery>(ECollisionChannel::ECC_WorldDynamic));
	
	TArray<AActor*> IgnoredTargtes;

	IgnoredTargtes.Add(this);
	
	TArray<AActor*> OutTragtes;

	FVector StartPosition = GetActorLocation();
	
	bool overlaped = UKismetSystemLibrary::SphereOverlapActors(this, StartPosition, 500.0f,
		ObjectTypes,ALightsTheRite::StaticClass(),IgnoredTargtes, OutTragtes);

	if(overlaped)
	{
		for (auto ObjectType : OutTragtes)
		{
			auto light = CastChecked<ALightsTheRite>(ObjectType);
			light->SetAggressiveMaterial();
		}
	}
}

void ATiffany::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(static_cast<EObjectTypeQuery>(ECollisionChannel::ECC_WorldDynamic));
	
	TArray<AActor*> IgnoredTargtes;

	IgnoredTargtes.Add(this);
	
	TArray<AActor*> OutTragtes;

	FVector StartPosition = GetActorLocation();
	
	bool overlaped = UKismetSystemLibrary::SphereOverlapActors(this, StartPosition, 500.0f,
		ObjectTypes,ALightsTheRite::StaticClass(),IgnoredTargtes, OutTragtes);

	if(overlaped)
	{
		for (auto ObjectType : OutTragtes)
		{
			auto light = Cast<ALightsTheRite>(ObjectType);
			light->SetNormalMaterial();
		}
	}
}
